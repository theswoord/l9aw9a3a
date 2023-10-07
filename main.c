/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:50:35 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/07 21:53:42 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell				g_struct;
	int					i;
	char				*test;
	struct sigaction	minisignols;

	i = 0;
	(void)ac;
	(void)av;
	minisignols.sa_handler = sig;
	sigemptyset(&minisignols.sa_mask);
	sigaddset(&minisignols.sa_mask, SIGQUIT);
	minisignols.sa_flags = 0;
	sigaction(SIGINT, &minisignols, NULL);
	sigaction(SIGQUIT, &minisignols, NULL);
	initialize_environment(&g_struct, &g_struct.envlist, env);
	while (1)
	{
		test = readline("minishell -> : ");
		if (!test)
		{
			free(test);
			free_env(g_struct.envlist);
			return (g_struct.exit_status);
		}
		if (ft_strlen(test) > 0)
			add_history(test);
		tokenisation(test, &g_struct, env);
		free(test);
	}
}
