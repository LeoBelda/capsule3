#include "wavgen.h"

static uint16_t	*random_freqs(size_t size, uint16_t low_limit, uint16_t high_limit)
{
	size_t		i;
	uint16_t	*tab;

	i = 0;
	tab = malloc(sizeof(uint16_t) * size);
	while (i < size)
	{
		tab[i] = rand() % (high_limit - low_limit) + low_limit;
		i++;
	}
	return (tab);
}

static float	*random_phases(size_t size)
{
	size_t		i;
	float		*tab;

	i = 0;
	tab = malloc(sizeof(uint16_t) * size);
	while (i < size)
	{
		tab[i] = ((float)(rand() % 4000 - 2000) / 2000.) * M_PI;
		i++;
	}
	return (tab);
}

void	prep_random(t_tabs *tabs)
{
	srand(time(NULL));
	tabs->rand_freqs = random_freqs(SIZE_RAND_TABS, 2, 2000);
	tabs->rand_phases = random_phases(SIZE_RAND_TABS);
}
