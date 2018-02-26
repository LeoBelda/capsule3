#ifndef SLAZZERS_H
# define SLAZZERS_H

# include <stdio.h>
# include <inttypes.h>
# include <string.h>

# define WAV_HEAD	44

typedef struct		s_image
{
	int		h;
	int		w;
	int		*pixels;
}					t_image;

typedef struct		s_samples
{
	int16_t	*src;
	int16_t	*gen;
	char	*wav_header;
	char	*name;
}					t_samples;

typedef struct		s_nnet
{
	size_t			num_input;
	size_t			num_hidden;
	size_t			num_output;
	double			eta;
	double			alpha;
	double			error;
	double			*input;
	double			*hidden;
	double			*output;
	double			*sum_h;
	double			*sum_o;
	double			*delta_h;
	double			*delta_o;
	double			**weight_ih;
	double			**weight_ho;
	double			**d_weight_ih;
	double			**d_weight_ho;
}					t_nnet;

t_nnet			*init_nnet(size_t num_input, size_t num_hidden,
							size_t num_output);
t_samples		*init_samples(char *name);
char			*gphoto2_command(unsigned int num);
void			fire_lasers(char *src_sample_name, char *g2c);
void			get_splatter_target(t_nnet *nn);
void			reload_cannons(t_samples *samples, t_nnet *nn);
void			adjust_aim(t_samples *samples, t_nnet *nn);
void			camera_init(char *name, char *folder);

#endif
