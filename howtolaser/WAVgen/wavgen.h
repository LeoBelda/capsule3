/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wavgen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 18:29:53 by lbelda            #+#    #+#             */
/*   Updated: 2018/02/13 14:15:41 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAVGEN_H
# define WAVGEN_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <inttypes.h>
# include <limits.h>
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

enum	e_err
{
	E_LOG,
	E_FATAL
};


int				prep_file(void);

void			error_exit(char *err_str, enum e_err type);

	
#endif
