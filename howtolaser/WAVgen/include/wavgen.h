#ifndef WAVGEN_H
# define WAVGEN_H

# include <alsa/asoundlib.h>

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <inttypes.h>
# include <limits.h>
# include <time.h>
# include <fcntl.h>
# include <math.h>
# include "SDL.h"

# define PATH_PREFIX "./bank/"
# define PATH_SUFFIX ".wav"
# define SHADER_NAME "./shaderz/new.wav"

# define NB_SAMPLES 44100
# define SAMPLE_RATE 44100
# define BITS_PER_SAMPLE 16
# define NB_CHANNELS 1

# define HEADER_SIZE 44
# define SC1_SIZE 16
# define AUDIO_FORMAT 1

# define NB_WAVEFORMS 4
# define MAX_RAND_TABS 2
# define MAX_NBFREQS 2

enum	e_err
{
	E_LOG,
	E_FATAL
};

enum	e_mode
{
	M_MACHINE,
	M_SHADERZ,
	M_PS3
};

typedef struct	s_env
{
	enum e_mode	mode;

	//SDL stuff
	int					quit;
	SDL_Window			*win;
	SDL_GameController	*controller;

	//ALSA stuff
	snd_pcm_t	*sd_handle;

	//machine learning elements

	size_t		nbfiles;

	float		(*funcs[NB_WAVEFORMS])(float, float, float, float);

	uint16_t	rand_nbfreqs;
	uint16_t	*rand_freqs;
	uint16_t	*rand_waves;
	float		*rand_phases;
}				t_env;

//INIT STUFF
void			write_header(int fd);
int				prep_file_machine(size_t i);
int				prep_file_shaderz(void);
void			init_random(t_env *e);
void			prep_random(t_env *e);

//MACHINE STUFF
void			machine_program(t_env *e);

float			gen_rand_triangles(float t, t_env *e);
float			gen_rand_sins(float t, t_env *e);
float			gen_rand_squares(float t, t_env *e);
float			gen_rand_sawtooth(float t, t_env *e);
float			gen_rand_rand(float t, t_env *e);

//SHADERZ STUFF
void			shaderz_program(t_env *e);

float			freq_swipe(uint32_t i, float low, float high);
float			freq_fuck(uint32_t i, float low, float high);
float			phase_swipe(uint32_t i);

//PS3 STUFF
void			ps3_program(t_env *e);

//MATH STUFF
float			gen_sin(float t, float freq, float a, float phase);
float			gen_triangle(float t, float freq, float a, float phase);
float			gen_sawtooth(float t, float freq, float a, float phase);
float			gen_square(float t, float freq, float a, float phase);
float			gen_fuck(float t, float freq, float a, float phase);

//ERROR STUFF
void			error_exit(char *err_str, enum e_err type);
void			usage_exit(void);

	
#endif
