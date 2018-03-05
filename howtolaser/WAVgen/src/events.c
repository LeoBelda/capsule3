#include "wavgen.h"

static	int		lissajou_found_ratio(t_env *e)
{
	int	i;
	float	c1, c2, ratio;

	i = 0;
	c1 = 2;
	c2 = 1;
	ratio = e->crv_beg[1].freq / (e->crv_beg[0].freq + 1);
	while (i < MAX_LISSAJOU)
	{
		if ((c1 / c2) > ratio && ((c1 + 1) / (c2 + 1)) <= ratio)
			return (i);
		i++;
	}
	return (0);
}

static void		handle_button_press(t_env *e, uint8_t button)
{
	float	ratio;
	switch (button)
	{
		case SDL_CONTROLLER_BUTTON_A:
			e->freq_select[1] = 0;
			break;
		case SDL_CONTROLLER_BUTTON_B:
			e->freq_select[1] = 1;
			break;
		case SDL_CONTROLLER_BUTTON_X:
			e->freq_select[1] = 2;
			break;
		case SDL_CONTROLLER_BUTTON_Y:
			e->freq_select[1] = 3;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			e->freq_select[0] = 0;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			e->freq_select[0] = 1;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			e->freq_select[0] = 2;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			e->freq_select[0] = 3;
		case SDL_CONTROLLER_BUTTON_GUIDE:
			printf("SELECT pressed\n");
			e->bci_mode += e->bci_mode % 2;
			break;
		case SDL_CONTROLLER_BUTTON_START:
			printf("START pressed\n");
			ratio = 1.0 + lissajou_found_ratio(e);
			e->crv_end[1].freq = ((1.0 + ratio) / ratio) * e->crv_end[0].freq;
			break;


	}
}

void		print_frequency(t_env *e)
{
	int	i;

	i = 0;
	while (i < e->curve_nb)
	{
		printf("curve[%i]: {%f, %f}  (Hz, amp)\n", i, e->crv_end[i].freq, e->crv_end[i].amp);
		i++;
	}
	printf("==\n");
}

void		handle_SDL_events(t_env *e)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			e->quit = 1;
		if (event.key.keysym.sym == SDLK_f)
		//	printf("{%f, %f}Hz:amp, {%fm %f}fHz\n", e->freq1, e->freq2);
			print_frequency(e);
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
