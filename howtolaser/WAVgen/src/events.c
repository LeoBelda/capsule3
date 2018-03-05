#include "wavgen.h"

static void		handle_button_press(t_env *e, uint8_t button)
{
	switch (button)
	{
		case SDL_CONTROLLER_BUTTON_A:
			e->freq2_select = 0;
			break;
		case SDL_CONTROLLER_BUTTON_B:
			e->freq2_select = 1;
			break;
		case SDL_CONTROLLER_BUTTON_X:
			e->freq2_select = 2;
			break;
		case SDL_CONTROLLER_BUTTON_Y:
			e->freq2_select = 3;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			e->freq1_select = 0;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			e->freq1_select = 1;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			e->freq1_select = 2;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			e->freq1_select = 3;
		case SDL_CONTROLLER_BUTTON_GUIDE:
			printf("SELECT pressed\n");
			e->bci_mode += e->bci_mode % 2;
			break;
	}
}

void		handle_SDL_events(t_env *e)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			e->quit = 1;
		if (event.key.keysym.sym == SDLK_f)
			printf("%fHz, %ffHz\n", e->freq1, e->freq2);
		if (event.type == SDL_CONTROLLERAXISMOTION)
		{
			e->inc1 = -0.5 *
		(float)SDL_GameControllerGetAxis(e->controller, 1) / (float)SHRT_MAX;
			e->inc2 = -0.5 *
		(float)SDL_GameControllerGetAxis(e->controller, 3) / (float)SHRT_MAX;
		}
		else if (event.type == SDL_CONTROLLERBUTTONDOWN)
			handle_button_press(e, event.cbutton.button);
		/*
		if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
			e->inc1 = -(float)event.caxis.value / (float)SHRT_MAX;
		if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
			e->inc2 = -(float)event.caxis.value / (float)SHRT_MAX;
			*/
	}
	return;
}
