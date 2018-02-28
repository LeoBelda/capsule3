#include "slazzers.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void	load_weights(t_nnet *nn, int fd)
{
	(void)nn;
	ft_printf("found a weight file ! closing...\n");
	close(fd);
	exit(0);
}

void	random_weights(t_nnet *nn)
{
	int		i;
	int		j;
	int		k;

	i = nn->num_hidden + 1;
	while (i-- - 1)
	{
		j = nn->num_input + 1;
		nn->weight_ih[0][i] = ((double)rand() / RAND_MAX) * 10 - 5;
		while (j-- - 1)
			nn->weight_ih[j][i] = ((double)rand() / RAND_MAX) / 1000;
	}
	j = nn->num_output + 1;
	while (j-- - 1)
	{
		k = nn->num_hidden + 1;
		nn->weight_ho[0][j] = ((double)rand() / RAND_MAX) * 10 - 5;
		while (k-- - 1)
		{
			nn->weight_ho[k][j] = ((double)rand() / RAND_MAX);
			//printf("one weight_ho : [%lf]\n", nn->weight_ho[j][k]);
		}

	}
}

void	init_weights(t_nnet *nn)
{
	int		fd;

	if ((fd = open("srcn.nn", O_RDONLY)) != -1)
		load_weights(nn, fd);
	else
		random_weights(nn);
}
