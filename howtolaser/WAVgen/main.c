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

static void	write_audio_data(int fd, t_tabs *tabs)
{
	int16_t		*data;
	uint32_t		i;

	i = 0;
	data = malloc(sizeof(int16_t) * NB_SAMPLES);
	while (i < NB_SAMPLES)
	{
		data[i] = gen_audio((float)i / (float)SAMPLE_RATE, tabs);
		i++;
	}
	write(fd, data, sizeof(int16_t) * NB_SAMPLES);
	free(data);
}

int	main(void)
{
	int		fd;
	t_tabs	*tabs;

	fd = prep_file();
	tabs = malloc(sizeof(t_tabs));
	prep_random(tabs);
	write_header(fd);
	write_audio_data(fd, tabs);
	return (0);
}
