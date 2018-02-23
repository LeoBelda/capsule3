#include "wavgen.h"

float	gen_rand_triangles(float t, t_env *e)
{
	uint16_t	i;
	float		total;
	float		a;

	i = 0;
	total = 0;
	a = 1. / (float)e->rand_nbfreqs;
	while (i < e->rand_nbfreqs)
	{
		total += gen_triangle(t, e->rand_freqs[i], a, e->rand_phases[i]);
		i++;
	}
	return (total * SHRT_MAX);
}

float	gen_rand_sins(float t, t_env *e)
{
	uint16_t	i;
	float		total;
	float		a;

	i = 0;
	total = 0;
	a = 1. / (float)e->rand_nbfreqs;
	while (i < e->rand_nbfreqs)
	{
		total += gen_sin(t, e->rand_freqs[i], a, e->rand_phases[i]);
		i++;
	}
	return (total * SHRT_MAX);
}

float	gen_rand_sawtooth(float t, t_env *e)
{
	uint16_t	i;
	float		total;
	float		a;

	i = 0;
	total = 0;
	a = 1. / (float)e->rand_nbfreqs;
	while (i < e->rand_nbfreqs)
	{
		total += gen_sawtooth(t, e->rand_freqs[i], a, e->rand_phases[i]);
		i++;
	}
	return (total * SHRT_MAX);
}

float	gen_rand_squares(float t, t_env *e)
{
	uint16_t	i;
	float		total;
	float		a;

	i = 0;
	total = 0;
	a = 1. / (float)e->rand_nbfreqs;
	while (i < e->rand_nbfreqs)
	{
		total += gen_square(t, e->rand_freqs[i], a, e->rand_phases[i]);
		i++;
	}
	return (total * SHRT_MAX);
}

float	gen_rand_rand(float t, t_env *e)
{
	uint16_t	i;
	float		total;
	float		a;

	i = 0;
	total = 0;
	a = 1. / (float)e->rand_nbfreqs;
	while (i < e->rand_nbfreqs)
	{
		total += e->funcs[e->rand_waves[i]]
			(t, e->rand_freqs[i], a, e->rand_phases[i]);
		i++;
	}
	return (total * SHRT_MAX);
}
