#include "slazzers.h"
#include "libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_gs(void)
{
	char		*buf;
	int			fd;
	struct stat	b;

	if((fd = open("gs.bmp", O_RDONLY)) == -1)
		exit(1);
	fstat(fd, &b);
	if (!(buf = malloc(b.st_size)))
		return (NULL);
	read(fd, buf, b.st_size);
	close(fd);
	return (buf);
}

double			normalize_to_double(int min, int max, int n)
{
	double	range;

	range = max - min;
	return ((n / range) + 0.5);
}

void			get_splatter_target(t_nnet *nn)
{
	int		s;
	int		i;
	char	*gs_full;
	char	*gs;

	system("convert *.jpg -resize x50 -colorspace GRAY -charcoal 2 -colors 256 gs.bmp");
	//system("mv *.jpg photos");
	if(!(gs_full = get_gs()))
		exit(1);
	s = *((int *)(&gs_full[10]));
	ft_printf("--\n\noffset = [ %d ]\n\n--\n", s);
	gs = &gs_full[s];
	i = nn->num_input;
	while (i--)
		nn->input[i] = normalize_to_double(-128, 127, (int)gs[i]);
	free(gs_full);
}
