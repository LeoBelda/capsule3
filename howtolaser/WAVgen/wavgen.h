#ifndef WAVGEN_H
# define WAVGEN_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <inttypes.h>
# include <limits.h>
# include <time.h>
# include <fcntl.h>
# include <math.h>

# define PATH_PREFIX "./rec/"
# define PATH_SUFFIX ".wav"

# define NB_SAMPLES 44100
# define SAMPLE_RATE 44100
# define BITS_PER_SAMPLE 16
# define NB_CHANNELS 1

# define HEADER_SIZE 44
# define SC1_SIZE 16
# define AUDIO_FORMAT 1

# define NB_WAVEFORMS 3
# define MAX_RAND_TABS 3
# define MAX_NBFREQS 3

enum	e_err
{
	E_LOG,
	E_FATAL
};

typedef struct	s_tabs
{
	float		(*funcs[NB_WAVEFORMS])(float, float, float, float);

	uint16_t	rand_nbfreqs;
	uint16_t	*rand_freqs;
	uint16_t	*rand_waves;
	float		*rand_phases;
}				t_tabs;


float			gen_sin(float t, float freq, float a, float phase);
float			gen_triangle(float t, float freq, float a, float phase);
float			gen_square(float t, float freq, float a, float phase);

float			gen_rand_triangles(float t, t_tabs *tabs);
float			gen_rand_sins(float t, t_tabs *tabs);
float			gen_rand_squares(float t, t_tabs *tabs);
float			gen_rand_rand(float t, t_tabs *tabs);

void			prep_random(t_tabs *tabs);
void			init_random(t_tabs *tabs);
int				prep_file(size_t i);

void			error_exit(char *err_str, enum e_err type);
void			usage_exit(void);

	
#endif
