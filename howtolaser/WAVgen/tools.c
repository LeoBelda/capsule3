#include "wavgen.h"

int			prep_file(size_t i)
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
