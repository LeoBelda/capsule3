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
	(void)range;
	printf("double out : %lf\n", d);
	return ((int16_t)(d * USHRT_MAX));
}

void		reload_samples(t_samples *samples, t_nnet *nn)
{
	int		i;
	int		fd;

	i = nn->num_output;
	while (i-- - 1)
	{
		samples->src[i] = samples->gen[i];
		printf("%hd\n", (samples->gen[i] = map_to_int16(0.0, 1.0, nn->output[i])));
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

	j = nn->num_hidden + 1;
	while (j-- - 1)
	{
		nn->sum_h[j] = nn->weight_ih[0][j];
		//printf("sum_h : [%lf]\n", nn->sum_h[j]);
		i = nn->num_input + 1;
		while (i-- - 1)
			nn->sum_h[j] += nn->input[i] * nn->weight_ih[i][j];
		//printf("sum_h :[%lf]\n", nn->sum_h[j]);
		//printf("hidden : [%lf]\n",(nn->hidden[j] = 1.0 / (1.0 + exp(-nn->sum_h[j]))));
	}
	k = nn->num_output + 1;
	while (k-- - 1)
	{
		nn->sum_o[k] = nn->weight_ho[0][k];
		printf("sum_o :[%lf]\n", nn->sum_o[k]);
		j = nn->num_hidden + 1;
		while (j-- - 1)
			nn->sum_o[k] += nn->hidden[j] * nn->weight_ho[j][k];
		nn->output[k] = 1.0 / (1.0 + exp(-nn->sum_o[k]));
		printf("sum_o :[%lf]\n", nn->sum_o[k]);
		printf("output : [%lf]\n",(nn->output[k] = 1.0 / (1.0 + exp(-nn->sum_o[k]))));
	}
	reload_samples(samples, nn);
}
