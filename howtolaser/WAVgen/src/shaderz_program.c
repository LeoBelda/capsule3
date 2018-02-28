#include "wavgen.h"

static void	write_shaderz(int fd, t_env *e)
{
	int16_t		*data;
	uint32_t		i;

	(void)e;
	i = 0;
	data = malloc(sizeof(int16_t) * NB_SAMPLES);
	while (i < NB_SAMPLES)
	{
		data[i] = gen_square((float)i / (float)SAMPLE_RATE,
				 4 , 1., 0) * SHRT_MAX;
		//data[i] += (gen_triangle((float)i / (float)SAMPLE_RATE,
		//			freq_swipe(i, 48, 102), 0.32, 0) * SHRT_MAX);
		//data[i] += (gen_sin((float)i / (float)SAMPLE_RATE,
		//			freq_swipe(i, 300.2, 300.1), 0.32, 0.) * SHRT_MAX);
	//	data[i] += (gen_sin((float)i / (float)SAMPLE_RATE,
	//				freq_swipe(i, 17.5, 35), 0.25, 0.) * SHRT_MAX);
		i++;
	}
	write(fd, data, sizeof(int16_t) * NB_SAMPLES);
	free(data);

}

void	shaderz_program(t_env *e)
{
	int	fd;

	fd = 0;
	fd = prep_file_shaderz();
	write_header(fd);
	write_shaderz(fd, e);
}
