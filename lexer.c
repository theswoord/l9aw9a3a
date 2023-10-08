/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:32:36 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 06:09:24 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenisation(char *str, t_shell *mstruct, char **env)
{
	char	**single_comm;
	char	**done;
	int		docs;

	if (allspaces(str) == 1 || ft_strlen(str) == 0)
	{
		return ;
	}
	done = ft_u_split(str);
	add_token_list(&mstruct->tlist, done);
	free_tableau(done, twodlen(done));
	modify_env(mstruct, mstruct->tlist);
	update_exit(mstruct);
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
	expander_init(mstruct, mstruct->tlist, NULL);

	
	if (command_id(mstruct->tlist) == PIPE
		||command_id(mstruct->tlist) == REDIW
		|| command_id(mstruct->tlist) == REDIR
		|| command_id(mstruct->tlist) == APPEND || command_id(mstruct->tlist) == DOC )
	{
		files_finder(mstruct->tlist);
		redi_set(mstruct);
		pipes_divider(mstruct);
		execute_pipelines(&mstruct->pipes_list, mstruct);
		update_exit(mstruct);
		mstruct->redi_list = NULL;

		if((command_id(mstruct->tlist) == REDIW
		|| command_id(mstruct->tlist) == REDIR
		|| command_id(mstruct->tlist) == APPEND || command_id(mstruct->tlist) == DOC)) 
		{
			free(mstruct->tlist);
		}
	}
	else
	{
		single_comm = from_list_to_arr(mstruct->tlist);
		general_execution(mstruct, single_comm, 1);
		update_exit(mstruct);
		free(single_comm);
		free_tokens(mstruct->tlist);
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
		pipes_list(mstruct, b);
		i++;
	}
	if (mstruct->redi_list != NULL)
	{
		// printf("\t%p\n", cu);
		cu = mstruct->pipes_list;
		// printf("\t%p\n", cu);
		while (cu && cu->next)
			cu = cu->next;
		cu->redirect = mstruct->redi_list;
	}
}
