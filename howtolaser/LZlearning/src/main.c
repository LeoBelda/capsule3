#include "libft.h"
#include "slazzers.h"
#include <stdlib.h>
#include <unistd.h>

#define IMG_W	64
#define IMG_H	43
#define HIDDEN	1024
#define SAMPLE	1250

void	camera_init(char *name, char *folder)
{
	char	*syscall;

	syscall = ft_strjoin("gphoto2 --camera=", name);
	system(syscall);
	free(syscall);
	syscall = ft_strjoin("mkdir ", folder);
	system(syscall);
	system("gphoto2 --keep");
	free(syscall);
}

int		main(int argc, char **argv)
{
	unsigned int	count;
	t_samples		*samples;
	char			*g2_command;
	t_nnet			*nn;

	if (argc != 5)
	{
		ft_printf("Program must have 4 args :\n\
		1:folder for images\n\
		2:starting index for file numerotation (WARNING : do NOT use existing file index)\n\
		3:file path to first sample\n\
		4:number of iterations\n");
		return (1);
	}
	g2_command = gphoto2_command(atoi(argv[2]));
	count = atoi(argv[4]);
	if(!(samples = init_samples(argv[3])))
		return (1);
	camera_init("\"Nikon DSC D80 (PTP mode)\"", argv[1]);
	nn = init_nnet(IMG_W * IMG_H, HIDDEN, SAMPLE);
	init_weights(nn);
	while (count--)
	{
	printf("1\n");
		fire_lasers(samples->name, g2_command);
	printf("2\n");
		get_splatter_target(nn);
	printf("3\n");
		reload_cannons(samples, nn);
	printf("4\n");
		adjust_aim(samples, nn);
	printf("5\n");
	}
	printf("finishe dlol\n");
	return (0);
}
