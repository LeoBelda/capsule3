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

# define PATH "./rec/0001.wav"

# define NB_SAMPLES 441000
# define SAMPLE_RATE 44100
# define BITS_PER_SAMPLE 16
# define NB_CHANNELS 1

# define HEADER_SIZE 44
# define SC1_SIZE 16
# define AUDIO_FORMAT 1

# define SIZE_RAND_TABS 5

enum	e_err
{
	E_LOG,
	E_FATAL
};

typedef struct	s_tabs
{
	uint16_t	*rand_freqs;
	float		*rand_phases;
}				t_tabs;

int16_t			gen_audio(float t, t_tabs *tabs);

void			prep_random(t_tabs *tabs);
int				prep_file(void);

void			error_exit(char *err_str, enum e_err type);

	
#endif
