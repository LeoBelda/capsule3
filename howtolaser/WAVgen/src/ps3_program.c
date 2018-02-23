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

static void		handle_SDL_events(t_env *e)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			return (1);
		/*
		if (iabs(event.caxis.value) <= 5500)
			event.caxis.value = 0;
		if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
			ps3_camroty(e, event.caxis.value);
		else if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
			ps3_camrotx(e, event.caxis.value);
		else if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
			ps3_camroty(e, event.caxis.value);
		else if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
			ps3_camrotx(e, event.caxis.value);
		*/
	}
	return (0);
}

void		ps3_program(t_env *e)
{
	init_SDL(e);
	init_alsa(e);
	while (!e->quit)
	{
		handle_SDL_events(e);
		/*
		gen_audio_
		snd_pcm_writei(
		*/
	}
	snd_pcm_close(e->sd_handle);
	close_SDL(e);
}
