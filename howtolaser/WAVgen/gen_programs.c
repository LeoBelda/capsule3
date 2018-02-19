#include "wavgen.h"

float	gen_rand_triangles(float t, t_tabs *tabs)
{
	uint16_t	i;
	float		total;
	float		a;

	i = 0;
	total = 0;
	a = 1. / (float)tabs->rand_nbfreqs;
	while (i < tabs->rand_nbfreqs)
	{
		total += gen_triangle(t, tabs->rand_freqs[i], a, tabs->rand_phases[i]);
		i++;
	}
	return (total * SHRT_MAX);
}

float	gen_rand_sins(float t, t_tabs *tabs)
{
	uint16_t	i;
	float		total;
	float		a;

	i = 0;
	total = 0;
	a = 1. / (float)tabs->rand_nbfreqs;
	while (i < tabs->rand_nbfreqs)
	{
		total += gen_sin(t, tabs->rand_freqs[i], a, tabs->rand_phases[i]);
		i++;
	}
	return (total * SHRT_MAX);
}

float	gen_rand_squares(float t, t_tabs *tabs)
{
	uint16_t	i;
	float		total;
	float		a;

	i = 0;
	total = 0;
	a = 1. / (float)tabs->rand_nbfreqs;
	while (i < tabs->rand_nbfreqs)
	{
		total += gen_square(t, tabs->rand_freqs[i], a, tabs->rand_phases[i]);
		i++;
	}
	return (total * SHRT_MAX);
}

float	gen_rand_rand(float t, t_tabs *tabs)
{
	uint16_t	i;
	float		total;
	float		a;

	i = 0;
	total = 0;
	a = 1. / (float)tabs->rand_nbfreqs;
	while (i < tabs->rand_nbfreqs)
	{
		total += tabs->funcs[tabs->rand_waves[i]]
			(t, tabs->rand_freqs[i], a, tabs->rand_phases[i]);
		i++;
	}
	return (total * SHRT_MAX);
}
