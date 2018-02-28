#include "slazzers.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdio.h>

static void		update_g2c(char *g2c)
{
	char	*snum;
	int		n;

	snum = &g2c[23];
	n = atoi(snum);
	n += 1;
	snum[0] = '0' + (n / 100000) % 10;
	snum[1] = '0' + (n / 10000) % 10;
	snum[2] = '0' + (n / 1000) % 10;
	snum[3] = '0' + (n / 100) % 10;
	snum[4] = '0' + (n / 10) % 10;
	snum[5] = '0' + (n / 1) % 10;
}

void			fire_lasers(char *src_sample_name, char *g2c)
{
	FILE	*f1;
	FILE	*f2;
	char	*command;

	if(!(command = ft_strjoin("mplayer -really-quiet ", src_sample_name)))
		exit(1);
	f1 = popen(command, "r");
	free(command);
	f2 = popen(g2c, "w");
	pclose(f1);
	pclose(f2);
	update_g2c(g2c);
	//sleep(3.8);
}
