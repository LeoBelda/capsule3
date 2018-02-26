#include "wavgen.h"

static void	parse_args(t_env *e, int argc, char **argv)
{
	if ((argc != 2 && argc != 3) || (strcmp(argv[1], "machine")
				&& strcmp(argv[1], "shaderz")
				&& strcmp(argv[1], "ps3")))
		usage_exit();
	if (!strcmp(argv[1], "machine"))
	{
		if (argc != 3 || atoi(argv[2]) <= 0)
			usage_exit();
		else
		{
			e->mode = M_MACHINE;
			e->nbfiles = (size_t)atoi(argv[2]);
		}
	}
	else if (!strcmp(argv[1], "shaderz"))
	{
		if (argc != 2)
			usage_exit();
		else
			e->mode = M_SHADERZ;
	}
	else if (!strcmp(argv[1], "ps3"))
	{
		if (argc != 2)
			usage_exit();
		else
			e->mode = M_PS3;
	}
}

int	main(int argc, char **argv)
{
	t_env	*e;

	e = malloc(sizeof(t_env));
	parse_args(e, argc, argv);
	switch (e->mode)
	{
		case M_MACHINE:
			machine_program(e);
			break;
		case M_SHADERZ:
			shaderz_program(e);
			break;
		case M_PS3:
			ps3_program(e);
			break;
		default:
			break;
	}
	return (0);
}
