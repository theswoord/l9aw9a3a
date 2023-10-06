/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:32:36 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 04:37:29 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenisation(char *str, t_shell *g_struct, char **env)
{
	char	**single_comm;
	char	**done;

	if (allspaces(str) == 1 || ft_strlen(str) == 0)
	{
		return ;
	}
	done = ft_u_split(str);
	add_token_list(&g_struct->tlist, done);
	free_tableau(done, twodlen(done));
	modify_env(g_struct, g_struct->tlist);
	update_exit(g_struct);
	if (list_check(g_struct->tlist))
		qidentify(g_struct, g_struct->tlist);
	else
	{
		g_struct->exit_status = 258;
		update_exit(g_struct);
		printf("minishell: syntax error\n");
		return ;
	}
	expander_init(g_struct, g_struct->tlist, NULL);
	if (command_id(g_struct->tlist) == REDIW
		|| command_id(g_struct->tlist) == REDIR
		|| command_id(g_struct->tlist) == APPEND)
	{
		files_finder(g_struct->tlist);
		redi_set(g_struct);
		pipes_divider(g_struct);
		execute_pipelines(&g_struct->pipes_list, env, g_struct);
		update_exit(g_struct);
		add_env_var(&g_struct->envlist, "?", g_struct->exit_arr);
		g_struct->redi_list = NULL;
		free_tokens(g_struct->tlist);
	}
	else if (command_id(g_struct->tlist) == PIPE)
	{
		pipes_divider(g_struct);
		execute_pipelines(&g_struct->pipes_list, env, g_struct);
		update_exit(g_struct);
		add_env_var(&g_struct->envlist, "?", g_struct->exit_arr);
	}
	else
	{
		single_comm = from_list_to_arr(g_struct->tlist);
		builtins(g_struct, env, single_comm);
		if (ft_strcmp(single_comm[0], "cd") != 0 && ft_strcmp(single_comm[0],
				"export") != 0 && ft_strcmp(single_comm[0], "env") != 0
			&& ft_strcmp(single_comm[0], "pwd") != 0
			&& ft_strcmp(single_comm[0], "echo") != 0
			&& ft_strcmp(single_comm[0], "unset") != 0
			&& ft_strcmp(single_comm[0], "exit") != 0)
		{
			execute_commands(single_comm[0], single_comm, env, g_struct);
			update_exit(g_struct);
			add_env_var(&g_struct->envlist, "?", g_struct->exit_arr);
		}
		free(single_comm);
		free_tokens(g_struct->tlist);
	}
}

int	command_id(t_tlist *head)
{
	t_tlist	*current;

	current = head;
	while (current != NULL)
	{
		if (current->value == PIPE)
			return (PIPE);
		if (current->value == REDIW)
			return (REDIW);
		if (current->value == REDIR)
			return (REDIR);
		if (current->value == APPEND)
			return (APPEND);
		current = current->next;
	}
	return (99);
}

void	pipes_divider(t_shell *g_struct)
{
	static t_tlist	*current;
	int				i;
	int				b;
	int				a;
	t_node			*cu;

	g_struct->pipes_list = NULL;
	current = g_struct->tlist;
	i = 0;
	b = 0;
	a = element_counter(g_struct->tlist, PIPE) + 1;
	while (i < a)
	{
		b = nodes_count(&current);
		pipes_list(g_struct, b);
		i++;
	}
	if (g_struct->redi_list != NULL)
	{
		cu = g_struct->pipes_list;
		while (cu && cu->next)
			cu = cu->next;
		cu->redirect = g_struct->redi_list;
	}
}
