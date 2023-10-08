/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:32:36 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 07:58:36 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_who(t_shell *m)
{
	char	**single_comm;

	if (command_id(m->tlist) == PIPE || command_id(m->tlist) == REDIW
		|| command_id(m->tlist) == REDIR || command_id(m->tlist) == APPEND
		|| command_id(m->tlist) == DOC)
	{
		files_finder(m->tlist);
		redi_set(m);
		pipes_divider(m);
		execute_pipelines(&m->pipes_list, m);
		update_exit(m);
		m->redi_list = NULL;
		if ((command_id(m->tlist) == REDIW || command_id(m->tlist) == REDIR
				|| command_id(m->tlist) == APPEND
				|| command_id(m->tlist) == DOC))
			free(m->tlist);
	}
	else
	{
		single_comm = from_list_to_arr(m->tlist);
		general_execution(m, single_comm, 1);
		update_exit(m);
		free(single_comm);
		free_tokens(m->tlist);
	}
}

void	decoupe(char *str, t_shell *mstruct)
{
	char	**done;

	done = ft_u_split(str);
	add_token_list(&mstruct->tlist, done);
	free_tableau(done, twodlen(done));
	modify_env(mstruct, mstruct->tlist);
	update_exit(mstruct);
}

void	tokenisation(char *str, t_shell *mstruct, int ac, char **av)
{
	int	docs;

	if (allspaces(str) == 1 || ft_strlen(str) == 0)
		return ;
	(void)ac;
	(void)av;
	decoupe(str, mstruct);
	if (list_check(mstruct->tlist))
		qidentify(mstruct, mstruct->tlist);
	else
	{
		mstruct->exit_status = 258;
		update_exit(mstruct);
		printf("minishell: syntax error\n");
		free_tokens(mstruct->tlist);
		return ;
	}
	if (command_id(mstruct->tlist) == DOC)
	{
		mstruct->heredoc_list = NULL;
		docs = element_counter(mstruct, mstruct->tlist, DOC);
	}
	expander_init(mstruct, mstruct->tlist);
	exec_who(mstruct);
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
		if (current->value == DOC)
			return (DOC);
		current = current->next;
	}
	return (0);
}

void	pipes_divider(t_shell *mstruct)
{
	static t_tlist	*current;
	int				i;
	int				b;
	int				a;
	t_node			*cu;

	mstruct->pipes_list = NULL;
	current = mstruct->tlist;
	i = 0;
	b = 0;
	a = element_counter(mstruct, mstruct->tlist, PIPE) + 1;
	while (i < a)
	{
		b = nodes_count(&current);
		pipes_list(mstruct, b, 0);
		i++;
	}
	if (mstruct->redi_list != NULL)
	{
		cu = mstruct->pipes_list;
		while (cu && cu->next)
			cu = cu->next;
		cu->redirect = mstruct->redi_list;
	}
}
