#include "slazzers.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char		*get_suffix(unsigned int num)
{
	char	*snum;
	char	*suffix;

	if (!(snum = ft_strdup("000000")))
		return (NULL);
	snum[0] += (num / 100000) % 10;
	snum[1] += (num / 10000) % 10;
	snum[2] += (num / 1000) % 10;
	snum[3] += (num / 100) % 10;
	snum[4] += (num / 10) % 10;
	snum[5] += (num / 1) % 10;
	if (!(suffix = ft_strjoin(snum, ".wav\"")))
		return (NULL);
	free(snum);
	return (suffix);
}

char			*gphoto2_command(unsigned int num)
{
	char	*suffix;
	char	*command;
	char	*tmp;

	if (!(suffix = get_suffix(num)))
		return (NULL);
	if (!(command = ft_strjoin("gphoto2 --filename=\"img", suffix)))
		return (NULL);
	tmp = command;
	if (!(command =
		ft_strjoin(command, " --capture-image-and-download")))
		return (NULL);
	free(tmp);
	free(suffix);
	return (command);
}
