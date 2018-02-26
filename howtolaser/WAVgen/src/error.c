#include "wavgen.h"

void	error_exit(char *err_str, enum e_err type)
{
	printf("%s\n", err_str);
	if (type == E_FATAL)
		exit(EXIT_FAILURE);
	else
		return ;
}

void	usage_exit(void)
{
	printf("usage: WAVgen nb_samples_out");
	exit(EXIT_FAILURE);
}
