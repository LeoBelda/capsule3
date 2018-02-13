#include "wavgen.h"

int			prep_file(void)
{
	int		fd;
	char	*path = PATH;

	fd = 0;
	if (!(fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777)))
		error_exit("Couldnt create file", E_FATAL);
	return (fd);
}
