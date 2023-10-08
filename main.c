/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:50:35 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 06:09:24 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell				mstruct;
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
	initialize_environment(&mstruct, &mstruct.envlist, env);
	while (1)
	{
		test = readline("minishell -> : ");
		if (!test)
		{
			free(test);
			free_env(mstruct.envlist);
			return (mstruct.exit_status);
		}
		if (ft_strlen(test) > 0)
			add_history(test);
		tokenisation(test, &mstruct, env);
		free(test);
	}
}
