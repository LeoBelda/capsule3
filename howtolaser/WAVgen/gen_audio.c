#include "wavgen.h"

static float	gen_sin(float t, float freq, float a, float phase)
{
	return (a * sinf(freq * 2. * M_PI * t + phase));
}

static float	gen_rand_sins(float t, uint16_t nb, t_tabs *tabs)
{
	uint16_t	i;
	float		total;
	float		a;

	i = 0;
	total = 0;
	a = 1. / (float)nb;
	while (i < nb)
	{
		total += gen_sin(t, tabs->rand_freqs[i], a, tabs->rand_phases[i]);
		i++;
	}
	return (total);
}

int16_t		gen_audio(float t, t_tabs *tabs)
{
	return (SHRT_MAX * gen_rand_sins(t, SIZE_RAND_TABS, tabs));
}
