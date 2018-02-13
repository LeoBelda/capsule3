#include "wavgen.h"

static void	random_freqs(size_t size, uint16_t *tab, uint16_t low_limit, uint16_t high_limit)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		tab[i] = (rand() % (high_limit - low_limit) + low_limit) * 10.;
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

void	prep_random(t_tabs *tabs)
{
	random_freqs(SIZE_RAND_TABS, tabs->rand_freqs, 2, 2000);
	random_phases(SIZE_RAND_TABS, tabs->rand_phases);
}

void	init_random(t_tabs *tabs)
{
	srand(time(NULL));
	tabs->rand_freqs = malloc(sizeof(uint16_t) * SIZE_RAND_TABS);
	tabs->rand_phases = malloc(sizeof(float) * SIZE_RAND_TABS);
}
