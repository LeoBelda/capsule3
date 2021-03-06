#ifndef WAVGEN_H
# define WAVGEN_H

# include <alsa/asoundlib.h>
# include "tinyosc.h"

# include <arpa/inet.h>
# include <sys/select.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
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

# define PERIOD_SIZE 512
# define BUFFER_SIZE PERIOD_SIZE * 4

# define HEADER_SIZE 44
# define SC1_SIZE 16
# define AUDIO_FORMAT 1

# define NB_WAVEFORMS 4
# define MAX_RAND_TABS 1
# define MAX_NBFREQS 1

# define NB_BCI 5
# define NB_FREQS 4

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

	float		freq1;
	float		freq2;
	float		amp1;
	float		amp2;
	float		freqs[NB_FREQS];

	float		incf1;
	float		incf2;
	float		inca1;
	float		inca2;
	float		phase1;
	float		phase2;

	float		data_bci[5];
	float		prev_bci[5];

	size_t		freq1_select;
	size_t		freq2_select;

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
void			prep_funcs(float (*f[])(float, float, float, float));

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

void			handle_SDL_events(t_env *e);
void 			tosc_bci(tosc_message *osc, t_env *e);

//MATH STUFF
float			gen_sin(float t, float freq, float a, float phase);
float			gen_sin_live(float t, float freq, float a, float phase);
float			gen_triangle(float t, float freq, float a, float phase);
float			gen_sawtooth(float t, float freq, float a, float phase);
float			gen_square(float t, float freq, float a, float phase);
float			gen_fuck(float t, float freq, float a, float phase);

//ERROR STUFF
void			error_exit(char *err_str, enum e_err type);
void			usage_exit(void);

	
#endif
