#include "slazzers.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


t_samples	*init_samples(char *name)
{
	t_samples	*samples;
	struct stat	b;
	int			fd;

	if (!(samples = malloc(sizeof(t_samples))))
		return (NULL);
	samples->name = ft_strdup("def.wav");
	if (!samples->name)
		return (NULL);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	fstat(fd, &b);
	if (!(samples->wav_header = malloc(WAV_HEAD)))
		return (NULL);
	if (!(samples->src = malloc(b.st_size - WAV_HEAD)))
		return (NULL);
	if (!(samples->gen = malloc(b.st_size - WAV_HEAD)))
		return (NULL);
	read(fd, samples->wav_header, WAV_HEAD);
	printf("read [ %ld ] samples from file\n", read(fd, samples->src, b.st_size - WAV_HEAD));
	return (samples);
}
