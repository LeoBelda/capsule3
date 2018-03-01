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
	printf("total size of bmp : [ %ld ]\n", read(fd, buf, b.st_size));
	close(fd);
	return (buf);
}

double			normalize_to_double(int min, int max, unsigned char n)
{
	double	range;

	range = max - min;
	//printf("gs pixel : [%hhu]\n", n);
	//printf("double pixel :[%lf]\n", (n / range));
	return ((n / range) + 0.5);
}

void			get_splatter_target(t_nnet *nn)
{
	int		s;
	int		i;
	char	*gs_full;
	char	*gs;

	system("convert *.jpg -resize 64 -compress None -colorspace GRAY -charcoal 2 -colors 256 gs.bmp");
	//system("mv *.jpg photos");
	if(!(gs_full = get_gs()))
		exit(1);
	s = *((int *)(&gs_full[10]));
	ft_printf("file size : [ %d ] \n", *((int *)(&gs_full[2])));
	ft_printf("header size : [ %d ] \n", *((int *)(&gs_full[14])));
	ft_printf("image width : [ %d ] \n", *((int *)(&gs_full[18])));
	ft_printf("image height : [ %d ] \n", *((int *)(&gs_full[22])));
	ft_printf("image bpp : [ %hd ] \n", *((int16_t *)(&gs_full[28])));
	ft_printf("image compression : [ %d ] \n", *((int *)(&gs_full[30])));
	ft_printf("image size : [ %d ] \n", *((int *)(&gs_full[34])));
	ft_printf("--\n\noffset = [ %d ]\n\n--\n", s);
	gs = &gs_full[s];
	i = nn->num_input;
	while (i--)
		nn->input[i] = normalize_to_double(0, 256, (unsigned char)gs[i]);
	free(gs_full);
}
