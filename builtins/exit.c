#include "builtins.h"

int	ft_atoi(const char *str)
{
	int	b;
	int	ichara;
	int	l7asol;

	b = 0;
	ichara = 1;
	l7asol = 0;
	while ((str[b] >= 9 && str[b] <= 13) || str[b] == 32)
	{
		b++;
	}
	if (str[b] == '-' || str[b] == '+')
	{
		if (str[b] == '-')
			ichara *= -1;
		b++;
	}
	while (str[b] >= '0' && str[b] <= '9')
	{
		l7asol *= 10;
		l7asol += str[b] - '0';
		b++;
	}
	return (l7asol * ichara);
}

int	ft_isdigit(int a)
{
	if (a >= '0' && a <= '9')
		return (1);
	else
		return (0);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	valid_arg(char *arg)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (arg[i] == '-' || arg[i] == '+')
	{
		sign = -1;
		i++;
	}
	if (is_number(arg))
	{
		return (1);
	}
	return (0);
}

void	ft_exit(char **args, t_shell *g_struct)
{
	int	exit_status;

	exit_status = 0;
	printf("exit\n");
	if (args[1])
	{
		if (valid_arg(args[1]))
			error_set(g_struct, TOO_MANY_ARGUMENTS, 1);
		else if (args[2])
			error_set(g_struct, NUMERIC_ARG_REQUIRED, 1);
		exit_status = ft_atoi(args[1]);
	}
	else
		exit_status = g_struct->exit_status;
	exit(exit_status);
}
