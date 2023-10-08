/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:44:41 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 04:46:35 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_exit_error(int case_num, char *command)
{
	char	*error_message;

	error_message = ft_strjoin("-bash: exit: ", command);
	error_message = ft_strjoin(error_message, ": numeric argument required\n");
	if (case_num == 1)
		ft_putstr_fd("-bash: exit: too many arguments\n", 2);
	else if (case_num == 2)
		ft_putstr_fd(error_message, 2);
	exit(255);
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
	if (args[1])
	{
		if (valid_arg(args[1]))
			ft_exit_error(2, args[1]);
		else if (args[2])
			ft_exit_error(1, NULL);
		exit_status = ft_atoi(args[1]);
	}
	else
	{
		exit_status = g_struct->exit_status;
	}
	exit(exit_status);
}
