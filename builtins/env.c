#include "builtins.h"

void	ft_env(t_shell *g_struct, int ac, char **av)
{
	print_env(g_struct->envlist, 0);
	error_set(g_struct, SUCCESS, 0);
}
