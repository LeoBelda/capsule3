#include "wavgen.h"
#include "tinyosc.h"

//volatile bool keepRunning = true;

//static void sigintHandler(int x) {
//  keepRunning = false;
//}

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

static void		gen_audio2(t_env *e, int16_t *buf)
{
	size_t			i;
	static float	phases[NB_FREQS];
	float			c1, c2;
	float			coef;

	i = 0;
	while (i < PERIOD_SIZE)
	{
		coef = (float)i / PERIOD_SIZE;
//		c1 = 
//				((1 - coef) * e->prev_bci[1] + coef * e->data_bci[1]) * 0.5;
//		c2 = 
//				((1 - coef) * e->prev_bci[3] + coef * e->data_bci[3]) * 0.5;
		buf[i] = e->funcs[e->freq1_select]((float)i / (float)SAMPLE_RATE,
				e->freq1, 0.5, phases[0]) * SHRT_MAX;
		buf[i] += e->funcs[e->freq2_select]((float)i / (float)SAMPLE_RATE,
				e->freq2 , 0.5, phases[1]) * SHRT_MAX;
		i++;
	}
	phases[0] = fmod(phases[0] +
			2 * M_PI * PERIOD_SIZE * e->freq1 / (float)SAMPLE_RATE,
			2 * M_PI);
	phases[1] = fmod(phases[1] +
			2 * M_PI * PERIOD_SIZE * e->freq2 / (float)SAMPLE_RATE,
			2 * M_PI);
}

/*
**	on va envoyer des baille de ouf trop generique ca mere. POPOPOOOOO!!
*/
static void		gen_audio(t_env *e, int16_t *buf)
{
	size_t	i, j;
	float	coef;
	float	time;
	float	ratio;
	t_acurv	curv;

	ratio = (float)SHRT_MAX / e->nb_freq;
	i = 0;
	while (i < PERIOD_SIZE)
	{
		j = 0;
		coef = (float)i / PERIOD_SIZE;
		buf[i] = 0;
		time = (float)i / SAMPLE_RATE;
		while (j < e->nb_freq)
		{
			curv.amp = ((1 - coef) * e->crv_beg[j].amp) + (coef * e->crv_end[j].amp);
			curv.freq = ((1 - coef) * e->crv_beg[j].freq) + (coef * e->crv_end[j].freq);
//			curv.phase = ((1 - coef) * (e->crv_beg[j].phase))
//					+ (coef * (e->crv_end[j].phase));
			curv.phase = e->crv_beg[j].phase;
			buf[i] += e->wave_form[e->freq_select[j]](time, &curv) * ratio;
			j++;
		}
		i++;
	}
	j = 0;
	while (j < e->nb_freq)
	{
		e->crv_beg[j] = e->crv_end[j];
		e->crv_end[j].phase = fmod(e->crv_end[j].phase +
				2 * M_PI * PERIOD_SIZE * e->crv_end[j].freq / (float)SAMPLE_RATE,
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
	e->crv_end[0].freq += e->inc1;
	e->crv_end[1].freq += e->inc2;
	if (e->crv_end[0].freq > 350 || e->crv_end[0].freq < 2)
		e->crv_end[0].freq = 120;
	if (e->crv_end[1].freq > 350 || e->crv_end[1].freq < 2)
		e->crv_end[1].freq = 160;
}

void	tosc_emg_bci(tosc_message *osc, t_env *e)
{
	int		chan;
	float	amp;

	//printf("Yi\n");
	if ((chan = tosc_getNextInt32(osc)) != 1 && chan != 3)
		return ;
	amp = tosc_getNextFloat(osc);
	amp = amp > 0.3 ? amp : 0.3;
	amp = amp < 0.9 ? amp : 0.9;
	e->prev_bci[chan] = e->data_bci[chan];
	e->data_bci[chan] = amp;
	e->data_bci[chan] = (e->data_bci[chan] > 1) ? 1: e->data_bci[chan];
	printf("chan:%d	val:%f\n", chan, amp);
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
		e->data_bci[i] = log10(tosc_getNextFloat(osc) + 1) / 3;
		e->data_bci[i] = (e->data_bci[i] > 1) ? 1: e->data_bci[i];
		i++;
	}
	printf("%d, %f, %f, %f, %f, %f\n", chan, e->data_bci[0], e->data_bci[1], e->data_bci[2],
			e->data_bci[3], e->data_bci[4]);
}

void		ps3_program_init(t_env *e)
{
	init_SDL(e);
	init_alsa(e);
	choose_freqs(e);
	waveforme_init(e->wave_form);
	osc_init(e, 9000);

//				       ||
// cette partie va probablement sauter vv
//  on la garde oiur continuer a compiler
	e->freq1 = 120.123;		
	e->freq2 = 160.878;
	e->crv_end[0].freq = e->freq1;
	e->crv_end[1].freq = e->freq2;
	e->nb_freq = 2;
	e->inc1 = 0;
	e->inc2 = 0;
	e->freq1_select = 0;
	e->freq2_select = 0;
}

void		push_sound(t_env *e, int16_t *buf, int periode_size)
{
	snd_pcm_sframes_t	frames;

	while (periode_size > 0)
	{
		frames = snd_pcm_writei(e->sd_handle, buf, periode_size);
		if (frames < 0)
		{
			frames = snd_pcm_recover(e->sd_handle, frames, 1);
			if (frames < 0)
				error_exit("Failed recovering pcm", E_FATAL);
			break;
		}
		periode_size -= frames;
		buf += frames;
	}
	refresh_freqs(e);
}

void		ps3_program(t_env *e)
{
	int16_t buf[BUFFER_SIZE * BITS_PER_SAMPLE];
	int16_t	*ptr;
	int		cptr;
	
	//test_osc(e);
	//exit(0);
	ps3_program_init(e);
	while (!e->quit)
	{
		handle_SDL_events(e);
		osc_get_message(e, test_osc_handler);
		// get osc_input
		// set/adapt waveforme parameter
		gen_audio(e, buf);
		push_sound(e, buf, PERIOD_SIZE);
	}
	snd_pcm_close(e->sd_handle);
	close_SDL(e);
}
