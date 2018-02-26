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

void	write_header(int fd)
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

int			prep_file_machine(size_t i)
{
	int		fd;
	char	*prefix = PATH_PREFIX;
	char	*suffix = PATH_SUFFIX;
	char	path[32];

	fd = 0;
	sprintf(path, "%s%06zu%s", prefix, i + 1, suffix);
	if (!(fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777)))
		error_exit("Couldnt create file", E_FATAL);
	return (fd);
}

int			prep_file_shaderz(void)
{
	int		fd;
	char	*path = SHADER_NAME;

	fd = 0;
	if (!(fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777)))
		error_exit("Couldnt create file", E_FATAL);
	return (fd);
}
