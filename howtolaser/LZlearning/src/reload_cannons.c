#include "slazzers.h"
#include <math.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int16_t		map_to_int16(double min, double max, double d)
{
	double	range;
	
	range = max - min;
	return ((int16_t)((d / range) * USHRT_MAX + SHRT_MIN));
}

void		reload_samples(t_samples *samples, t_nnet *nn)
{
	int		i;
	int		fd;

	i = nn->num_output;
	while (i-- - 1)
	{
		samples->src[i] = samples->gen[i];
		samples->gen[i] = map_to_int16(0.0, 1.0, nn->output[i]);
	}
	fd = open(samples->name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	write(fd, samples->wav_header, WAV_HEAD);
	i = 8;
	while (i--)
		write(fd, samples->gen, sizeof(int16_t) * nn->num_output);
	close(fd);
}

void		reload_cannons(t_samples *samples, t_nnet *nn)
{
	int		i;
	int		j;
	int		k;

	i = nn->num_input;
	j = nn->num_hidden;
	while (j-- - 1)
	{
	printf("HEY { %d }\n", j);
		nn->sum_h[j] = nn->weight_ih[0][j];
		while (i-- - 1)
			nn->sum_h[j] += nn->input[i] * nn->weight_ih[i][j];
		nn->hidden[j] = 1.0 / (1.0 + exp(-nn->sum_h[j]));
	}
	j = nn->num_hidden;
	k = nn->num_output;
	while (k-- - 1)
	{
		nn->sum_o[k] = nn->weight_ho[0][k];
		while (j-- - 1)
			nn->sum_o[k] += nn->hidden[j] * nn->weight_ho[j][k];
		nn->output[k] = 1.0 / (1.0 + exp(-nn->sum_o[k]));
	}
	reload_samples(samples, nn);
}
