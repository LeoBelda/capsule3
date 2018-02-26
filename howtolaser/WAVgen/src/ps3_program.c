#include "wavgen.h"

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

static void		gen_audio(int16_t *buf, float freq1, float freq2, float *phases)
{
	size_t	i;
	float	steps[2];

	i = 0;
	steps[0] = 2 * M_PI * PERIOD_SIZE * freq1 / (float)SAMPLE_RATE;
	steps[1] = 2 * M_PI * PERIOD_SIZE * freq2 / (float)SAMPLE_RATE;
	while (i < PERIOD_SIZE)
	{
		buf[i] = gen_sin((float)i / (float)SAMPLE_RATE,
				freq1, 0.5, phases[0]) * SHRT_MAX;
		buf[i] += gen_sin((float)i / (float)SAMPLE_RATE,
				freq2, 0.5, phases[1]) * SHRT_MAX;
		i++;
	}
	phases[0] = fmod(phases[0] + steps[0], 2 * M_PI);
	phases[1] = fmod(phases[1] + steps[1], 2 * M_PI);
}

static void		handle_SDL_events(t_env *e)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			e->quit = 1;
		if (event.key.keysym.sym == SDLK_f)
			printf("%fHz, %ffHz\n", e->freq1, e->freq2);
		if (abs(event.caxis.value) <= 5500)
			event.caxis.value = 0;
		e->inc1 = -0.25 * (float)SDL_GameControllerGetAxis(e->controller, 1) / (float)SHRT_MAX;
		e->inc2 = -0.25 * (float)SDL_GameControllerGetAxis(e->controller, 3) / (float)SHRT_MAX;
		/*
		if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
			e->inc1 = -(float)event.caxis.value / (float)SHRT_MAX;
		if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
			e->inc2 = -(float)event.caxis.value / (float)SHRT_MAX;
			*/
	}
	return;
}

void		ps3_program(t_env *e)
{
	snd_pcm_sframes_t	frames;
	int16_t buf[BUFFER_SIZE * BITS_PER_SAMPLE];
	int16_t	*ptr;
	int		cptr;
	float	phases[2];

	init_SDL(e);
	init_alsa(e);
	e->freq1 = 133;
	e->freq2 = 106;
	e->inc1 = 0;
	e->inc2 = 0;
	while (!e->quit)
	{
		handle_SDL_events(e);
		gen_audio(buf, e->freq1, e->freq2, phases);
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
		e->freq1 += e->inc1;
		e->freq2 += e->inc2;
	}
	snd_pcm_close(e->sd_handle);
	close_SDL(e);
}
