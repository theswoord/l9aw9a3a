#include "builtins.h"

// void    ft_clear_all()
// {

// }

int ft_atoi(const char *str)
{
	int b;
	int ichara;
	int l7asol;

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

// size_t	ft_strlen(const char *a)
// {
// 	size_t	b;

// 	b = 0;
// 	while (a[b])
// 	{
// 		b++;
// 	}
// 	return (b);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void ft_exit_error(int case_num, char *command)
{
	char *error_message;
	// print the output to stderr instead of standard output

	error_message = ft_strjoin("-bash: exit: ", command);
	error_message = ft_strjoin(error_message, ": numeric argument required\n");
	if (case_num == 1)
		ft_putstr_fd("-bash: exit: too many arguments\n", 2);
	else if (case_num == 2)
		ft_putstr_fd(error_message, 2);
	// ft_clear_all();
	exit(255);
}

int ft_isdigit(int a)
{
	if (a >= '0' && a <= '9')
		return (1);
	else
		return (0);
}

int is_number(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int valid_arg(char *arg)
{
	int i;
	int sign;

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

void ft_exit(char **args)
{
	int exit_status;

	exit_status = 0;
	printf("exit\n");
	if (args[1])
	{
		if (valid_arg(args[1]))
			ft_exit_error(2, args[1]);
		else if (args[2])
			ft_exit_error(1, NULL);
		exit_status = ft_atoi(args[1]);
	}
	// ft_clear_all();
	exit(exit_status);
}

// int main(int ac, char **av)
// {
// 	ft_exit(av);
// }

// Too many arguments: If the user provides additional arguments after the exit command, you can display an error message like "exit: too many arguments" and exit the shell with a non-zero status code.

// Invalid argument: If the user provides a non-numeric argument to the exit command, you can display an error message like "exit: numeric argument required" and exit the shell with a non-zero status code.

// Clean exit: If the user simply enters the exit command without any arguments, you can exit the shell gracefully with an exit status of 0.
