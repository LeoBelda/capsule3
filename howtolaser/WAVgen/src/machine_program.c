#include "wavgen.h"

static void	write_audio_data(int fd, t_env *e, size_t file)
{
	int16_t		*data;
	uint32_t		i;

	i = 0;
	data = malloc(sizeof(int16_t) * NB_SAMPLES);
	while (i < NB_SAMPLES)
	{
		switch (file % 5)
		{
			case 0:
				data[i] = gen_rand_sins(
						(float)i / (float)SAMPLE_RATE,
						e);
				break;
			case 1:
				data[i] = gen_rand_triangles(
						(float)i / (float)SAMPLE_RATE,
						e);
				break;
			case 2:
				data[i] = gen_rand_sawtooth(
						(float)i / (float)SAMPLE_RATE,
						e);
				break;
			case 3:
				data[i] = gen_rand_squares(
						(float)i / (float)SAMPLE_RATE,
						e);
				break;
			case 4:
				data[i] = gen_rand_rand(
						(float)i / (float)SAMPLE_RATE,
						e);
				break;
		}
		i++;
	}
	write(fd, data, sizeof(int16_t) * NB_SAMPLES);
	free(data);
}

void	machine_program(t_env *e)
{
	int		fd;
	size_t	i;

	fd = 0;
	i = 0;
	init_random(e);
	while (i < e->nbfiles)
	{
		fd = prep_file_machine(i);
		prep_random(e);
		write_header(fd);
		write_audio_data(fd, e, i);
		i++;
	}
}
