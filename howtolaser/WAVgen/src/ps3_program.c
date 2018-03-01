#include "wavgen.h"
#include "tinyosc.h"

static volatile bool keepRunning = true;

static void sigintHandler(int x) {
  keepRunning = false;
}

static void	init_SDL(t_env *e)
{
	if (SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO) < 0)
		error_exit("SDL Init failed", E_FATAL);
	if (!(e->win = SDL_CreateWindow("WAVgen", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					200, 200, SDL_WINDOW_FULLSCREEN_DESKTOP)))
		error_exit("SDL failed opening window", E_FATAL);

	SDL_GameControllerEventState(SDL_ENABLE);
	e->controller = SDL_GameControllerOpen(0);
}

static void	init_alsa(t_env *e)
{
	if (snd_pcm_open(&e->sd_handle, "default",
				SND_PCM_STREAM_PLAYBACK, 0))
		error_exit("failed opening alsa stream", E_FATAL);
	if (snd_pcm_set_params(e->sd_handle,
				SND_PCM_FORMAT_S16_LE,
				SND_PCM_ACCESS_RW_INTERLEAVED,
				NB_CHANNELS,
				SAMPLE_RATE,
				1,
				100000))
		error_exit("failed configuring alsa stream", E_FATAL);
}

static void	close_SDL(t_env *e)
{
	SDL_GameControllerClose(e->controller);
	SDL_GameControllerEventState(SDL_DISABLE);
	SDL_DestroyWindow(e->win);
	SDL_Quit();
}

static void		gen_audio(t_env *e, int16_t *buf)
{
	size_t			i, j;
	static float	phases[NB_FREQS];
	float			coef;
	float			amp[NB_FREQS];

	i = 0;
	while (i < PERIOD_SIZE)
	{
		j = 0;
		coef = (float)i / PERIOD_SIZE;
		buf[i] = 0;
		while (j < NB_FREQS)
		{
			amp[j] = 
				((1 - coef) * e->prev_bci[j] + coef * e->data_bci[j]) * 0.5;
			buf[i] +=
				e->funcs[e->freq1_select]((float)i / (float)SAMPLE_RATE,
				e->freqs[j], 1. / NB_FREQS, phases[j]) * SHRT_MAX;
			j++;
		}
	//	
	//	buf[i] = e->funcs[e->freq1_select]((float)i / (float)SAMPLE_RATE,
	//			e->freq1, c1 * 0.5, phases[0]) * SHRT_MAX;
	//	buf[i] += e->funcs[e->freq2_select]((float)i / (float)SAMPLE_RATE,
	//			e->freq1 + , c2 * 0.5, phases[1]) * SHRT_MAX;
		i++;
	}
	j = 0;
	while (j < NB_FREQS)
	{
		phases[j] = fmod(phases[j] +
				2 * M_PI * PERIOD_SIZE * e->freqs[j] / (float)SAMPLE_RATE,
				2 * M_PI);
		j++;
	}
}

static void	choose_freqs(t_env *e)
{
	e->freqs[0] = 100;
	e->freqs[1] = e->freqs[0] * 0.75;
	e->freqs[2] = e->freqs[1] * 0.75;
	e->freqs[3] = e->freqs[2] * 0.75;
}

static void	refresh_freqs(t_env *e)
{
	e->freq1 += e->inc1;
	e->freq2 += e->inc2;
	if (e->freq1 > 350 || e->freq1 < 2)
		e->freq1 = 133;
	if (e->freq2 > 350 || e->freq2 < 2)
		e->freq2 = 106;
}

void tosc_bci(tosc_message *osc, t_env *e) {
	uint32_t chan;
	float	data[NB_BCI];
	size_t	i;

	i = 0;
	if ((chan = tosc_getNextInt32(osc)) != 1 )
		return;
	while (i < NB_BCI)
	{
		e->prev_bci[i] = e->data_bci[i];
		e->data_bci[i] = log10(tosc_getNextFloat(osc) + 1);
		e->data_bci[i] /= 3;
		e->data_bci[i] = (e->data_bci[i] > 1) ? 1: e->data_bci[i];
		i++;
	}
	printf("%d, %f, %f, %f, %f, %f\n", chan, e->data_bci[0], e->data_bci[1], e->data_bci[2],
			e->data_bci[3], e->data_bci[4]);
}

void		ps3_program(t_env *e)
{
	snd_pcm_sframes_t	frames;
	int16_t buf[BUFFER_SIZE * BITS_PER_SAMPLE];
	int16_t	*ptr;
	int		cptr;

	init_SDL(e);
	init_alsa(e);
	choose_freqs(e);

	//
	//OpenBCI INIT
	//

	char buffer[2048]; // declare a 2Kb buffer to read packet data into

	printf("Starting write tests:\n");
	int len = 0;
	char blob[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	len = tosc_writeMessage(buffer, sizeof(buffer), "/address", "fsibTFNI",
			1.0f, "hello world", -1, sizeof(blob), blob);
	tosc_printOscBuffer(buffer, len);
	printf("done.\n");

	// register the SIGINT handler (Ctrl+C)
	signal(SIGINT, &sigintHandler);

	// open a socket to listen for datagrams (i.e. UDP packets) on port 9000
	const int fd = socket(AF_INET, SOCK_DGRAM, 0);
	fcntl(fd, F_SETFL, O_NONBLOCK); // set the socket to non-blocking
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(9000);
	sin.sin_addr.s_addr = INADDR_ANY;
	printf("addr:%d\n", INADDR_ANY);
	bind(fd, (struct sockaddr *) &sin, sizeof(struct sockaddr_in));
	printf("tinyosc is now listening on port 9000.\n");
	printf("Press Ctrl+C to stop.\n");

	//
	//
	//

	e->freq1 = 133;
	e->freq2 = 106;
	e->inc1 = 0;
	e->inc2 = 0;
	e->freq1_select = 0;
	e->freq2_select = 0;
	while (!e->quit && keepRunning)
	{
		handle_SDL_events(e);

		//
		// OpenBCI LOOP
		//

		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(fd, &readSet);
		struct timeval timeout = {0, 1000}; // select times out after 1 second
		if (select(fd+1, &readSet, NULL, NULL, &timeout) > 0) {
			struct sockaddr sa; // can be safely cast to sockaddr_in
			socklen_t sa_len = sizeof(struct sockaddr_in);
			int len = 0;
			while ((len = (int) recvfrom(fd, buffer, sizeof(buffer), 0, &sa, &sa_len)) > 0) {
				if (tosc_isBundle(buffer)) {
					tosc_bundle bundle;
					tosc_parseBundle(&bundle, buffer, len);
					const uint64_t timetag = tosc_getTimetag(&bundle);
					tosc_message osc;
					while (tosc_getNextMessage(&bundle, &osc)) {
						tosc_printMessage(&osc);
					}
				} else {
					tosc_message osc;
					tosc_parseMessage(&osc, buffer, len);
					tosc_bci(&osc, e);
				}
			}
		}

		//
		//
		//

		gen_audio(e, buf);
		cptr = PERIOD_SIZE;
		ptr = buf;
		while (cptr > 0)
		{
			frames = snd_pcm_writei(e->sd_handle, ptr, cptr);
			if (frames < 0)
			{
				frames = snd_pcm_recover(e->sd_handle, frames, 1);
				if (frames < 0)
					error_exit("Failed recovering pcm", E_FATAL);
				break;
			}
			cptr -= frames;
			ptr += frames;
		}
		refresh_freqs(e);
	}
	snd_pcm_close(e->sd_handle);
	close_SDL(e);
}
