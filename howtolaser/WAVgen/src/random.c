#include "wavgen.h"

static void	random_freqs(size_t size, uint16_t *tab, uint16_t low_limit, uint16_t high_limit)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		tab[i] = (rand() % (high_limit - low_limit) + low_limit);
		i++;
	}
}

static void	random_phases(size_t size, float *tab)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		tab[i] = ((float)(rand() % 4000 - 2000) / 2000.) * M_PI;
		i++;
	}
}

static void	random_waves(size_t size, uint16_t *tab)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		tab[i] = rand() % NB_WAVEFORMS;
		i++;
	}
}

void	prep_funcs(float (*f[])(float, float, float, float))
{
	f[0] = &gen_sin;
	f[1] = &gen_triangle;
	f[2] = &gen_square;
	f[3] = &gen_sawtooth;
}

void	prep_random(t_env *e)
{
	e->rand_nbfreqs = rand() % MAX_NBFREQS + 1;
	random_waves(e->rand_nbfreqs, e->rand_waves);
	random_freqs(e->rand_nbfreqs, e->rand_freqs, 8, 300);
	random_phases(e->rand_nbfreqs, e->rand_phases);
}

void	init_random(t_env *e)
{
	srand(time(NULL));
	e->rand_freqs = malloc(sizeof(uint16_t) * MAX_RAND_TABS);
	e->rand_waves = malloc(sizeof(float) * NB_WAVEFORMS);
	e->rand_phases = malloc(sizeof(float) * MAX_RAND_TABS);
}
