/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 18:29:24 by lbelda            #+#    #+#             */
/*   Updated: 2018/02/13 12:21:09 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	dprintf(fd, "RIFF");
	write(fd, &h_chunk_size, sizeof(uint32_t));
	dprintf(fd, "WAVE");

	// SUB CHUNK 1
	dprintf(fd, "fmt ");
	write(fd, &h_sc1_size, sizeof(uint32_t));
	write(fd, &h_audio_format, sizeof(uint16_t));
	write(fd, &h_nb_channels, sizeof(uint16_t));
	write(fd, &h_sample_rate, sizeof(uint32_t));
	write(fd, &h_byte_rate, sizeof(uint32_t));
	write(fd, &h_block_align, sizeof(uint16_t));
	write(fd, &h_bits_per_sample, sizeof(uint16_t));

	// SUB CHUNK 2
	dprintf(fd, "data");
	write(fd, &h_sc2_size, sizeof(uint32_t));
}

static int16_t	gen_sin(float t, float freq, float phase)
{
	return (SHRT_MAX * sinf(freq * 2. * M_PI * t + phase));
}

static void	gen_audio_data(int fd)
{
	int16_t	data[NB_SAMPLES];
	size_t		i;

	i = 0;
	while (i < NB_SAMPLES)
	{
		data[i] = gen_sin((float)i / (float)NB_SAMPLES, 440., 0.);
		i++;
	}
	write(fd, data, sizeof(int16_t) * NB_SAMPLES);
}

int	main(void)
{
	int		fd;

	fd = prep_file();
	write_header(fd);
	gen_audio_data(fd);
	return (0);
}
