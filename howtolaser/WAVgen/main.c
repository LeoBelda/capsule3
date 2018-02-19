#include "wavgen.h"

const uint32_t	h_sc1_size = SC1_SIZE;
const uint16_t	h_audio_format = AUDIO_FORMAT;
const uint16_t	h_nb_channels = NB_CHANNELS;
const uint32_t	h_sample_rate = SAMPLE_RATE;
const uint32_t	h_byte_rate = SAMPLE_RATE * NB_CHANNELS * BITS_PER_SAMPLE / 8;
const uint16_t	h_block_align = NB_CHANNELS * BITS_PER_SAMPLE / 8;
const uint16_t	h_bits_per_sample = BITS_PER_SAMPLE;

const uint32_t	h_sc2_size = NB_SAMPLES * NB_CHANNELS * BITS_PER_SAMPLE / 8;

const uint32_t	h_chunk_size = 4 + 8 + h_sc1_size + 8 + h_sc2_size;

static void	write_header(int fd)
{
	// RIFF CHUNK
	write(fd, "RIFF", 4);
	write(fd, &h_chunk_size, sizeof(uint32_t));
	write(fd, "WAVE", 4);

	// SUB CHUNK 1
	write(fd, "fmt ", 4);
	write(fd, &h_sc1_size, sizeof(uint32_t));
	write(fd, &h_audio_format, sizeof(uint16_t));
	write(fd, &h_nb_channels, sizeof(uint16_t));
	write(fd, &h_sample_rate, sizeof(uint32_t));
	write(fd, &h_byte_rate, sizeof(uint32_t));
	write(fd, &h_block_align, sizeof(uint16_t));
	write(fd, &h_bits_per_sample, sizeof(uint16_t));

	// SUB CHUNK 2
	write(fd, "data", 4);
	write(fd, &h_sc2_size, sizeof(uint32_t));
}

static void	write_audio_data(int fd, t_tabs *tabs, size_t file)
{
	int16_t		*data;
	uint32_t		i;

	i = 0;
	data = malloc(sizeof(int16_t) * NB_SAMPLES);
	while (i < NB_SAMPLES)
	{
		switch (file % 4)
		{
			case 0:
				data[i] = gen_rand_sins(
						(float)i / (float)SAMPLE_RATE,
						tabs);
				break;
			case 1:
				data[i] = gen_rand_triangles(
						(float)i / (float)SAMPLE_RATE,
						tabs);
				break;
			case 2:
				data[i] = gen_rand_squares(
						(float)i / (float)SAMPLE_RATE,
						tabs);
				break;
			case 3:
				data[i] = gen_rand_rand(
						(float)i / (float)SAMPLE_RATE,
						tabs);
				break;
		}
		i++;
	}
	write(fd, data, sizeof(int16_t) * NB_SAMPLES);
	free(data);
}

int	main(int argc, char **argv)
{
	size_t	nb_files;
	size_t	i;
	int		fd;
	t_tabs	*tabs;

	i = 0;
	if (argc != 2 || atoi(argv[1]) <= 0)
		usage_exit();
	nb_files = (size_t)atoi(argv[1]);
	tabs = malloc(sizeof(t_tabs));
	init_random(tabs);
	while (i < nb_files)
	{
		fd = prep_file(i);
		prep_random(tabs);
		write_header(fd);
		write_audio_data(fd, tabs, i);
		i++;
	}
	return (0);
}
