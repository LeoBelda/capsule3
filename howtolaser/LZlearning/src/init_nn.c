#include "slazzers.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void			mchecker(int mret)
{
	if (mret)
	{
		printf("Error malloc\n");
		exit(0);
	}
}

static void		init_dim1(t_nnet *nn)
{
	mchecker(
		!((nn->input = malloc(sizeof(double) * (nn->num_input + 1))) &&
		(nn->hidden = malloc(sizeof(double) * (nn->num_hidden + 1))) &&
		(nn->output = malloc(sizeof(double) * (nn->num_output + 1))) &&
		(nn->sum_h = malloc(sizeof(double) * (nn->num_hidden + 1))) &&
		(nn->sum_o = malloc(sizeof(double) * (nn->num_output + 1))) &&
		(nn->delta_h = malloc(sizeof(double) * (nn->num_hidden + 1))) &&
		(nn->delta_o = malloc(sizeof(double) * (nn->num_output + 1))) &&
		(nn->weight_ih = malloc(sizeof(double *) * (nn->num_input + 1))) &&
		(nn->weight_ho = malloc(sizeof(double *) * (nn->num_hidden + 1))) &&
		(nn->d_weight_ih = malloc(sizeof(double *) * (nn->num_input + 1))) &&
		(nn->d_weight_ho = malloc(sizeof(double *) * (nn->num_hidden + 1)))));
}

static void		init_dim2(t_nnet *nn)
{
	int		i;

	i = nn->num_input + 1;
	while (i--)
	{
		nn->weight_ih[i] = malloc(sizeof(double) * (nn->num_hidden + 1));
		nn->d_weight_ih[i] = malloc(sizeof(double) * (nn->num_hidden + 1));
		mchecker(!(nn->weight_ih[i] && nn->d_weight_ih[i]));
	}
	i = nn->num_hidden + 1;
	while (i--)
	{
		nn->weight_ho[i] = malloc(sizeof(double) * (nn->num_output + 1));
		nn->d_weight_ho[i] = malloc(sizeof(double) * (nn->num_output + 1));
		mchecker(!(nn->weight_ho[i] && nn->d_weight_ho[i]));
	}
}

t_nnet			*init_nnet(size_t num_input, size_t num_hidden, size_t num_output)
{
	t_nnet		*nn;

	mchecker(!(nn = malloc(sizeof(t_nnet))));
	nn->num_input = num_input;
	nn->num_hidden = num_hidden;
	nn->num_output = num_output;
	init_dim1(nn);
	init_dim2(nn);
	ft_bzero(nn->input, sizeof(double) * (num_input + 1));
	ft_bzero(nn->hidden, sizeof(double) * (num_hidden + 1));
	ft_bzero(nn->output, sizeof(double) * (num_output + 1));
	ft_bzero(nn->sum_h, sizeof(double) * (num_hidden + 1));
	ft_bzero(nn->sum_o, sizeof(double) * (num_output + 1));
	ft_bzero(nn->delta_h, sizeof(double) * (num_hidden + 1));
	ft_bzero(nn->delta_o, sizeof(double) * (num_output + 1));
	nn->eta = 0.1;
	nn->alpha = 0.0;
	nn->error = 0.0;
	return (nn);
}
