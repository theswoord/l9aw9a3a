#include "minishell.h"

void tokenisation(char *str, t_shell *g_struct, char **env)
{

	char **single_comm; // hadi kmala
	if (allspaces(str) == 1 || ft_strlen(str) == 0)
	{
		return;
	}

	char **done = ft_strsplit(str); // pit eveyone in a node

	add_token_list(&g_struct->tlist, done);

	free_tableau(done, twodlen(done));

	modify_env(g_struct, g_struct->tlist); // lmochkil ila kan chi 7aja wst param it's not it
	update_exit(g_struct);
	// add_env_var(&g_struct->envlist,"?",g_struct->exit_arr);
	// hadchi khdam
	// exit_status_error(g_struct,0);
	if (list_check(g_struct->tlist))
	{
		qidentify(g_struct, g_struct->tlist); // here nonini nonini moraja3a H rj3o a nabil
											  // print_tokens(g_struct->tlist);
	}
	else
	{
		g_struct->exit_status = 258;
		// printf("%d\n ",g_struct->exit_status);
		update_exit(g_struct);
		// add_env_var(&g_struct->envlist,"?",g_struct->exit_arr);
		printf("minishell: syntax error\n");
		return;
	}
	expander_init(g_struct, g_struct->tlist, NULL);
	// printf("hh\n");

	// if ()
	// {
	// 	/* code */
	// }
	// cd_command()

	// if ()
	// printf("hhhghghghg\n");
	// while (1)
	// {
	// 	/* code */
	// }

	if (command_id(g_struct->tlist) == REDIW || command_id(g_struct->tlist) == REDIR || command_id(g_struct->tlist) == APPEND)
	{
		files_finder(g_struct->tlist);
		redi_set(g_struct);
		pipes_divider(g_struct);

		// print_tokens(g_struct->tlist);
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
		// char **single_comm;								 // hadi kmala
		// single_comm = from_list_to_arr(g_struct->tlist); // this arr howa li aydkhl l function
		// printf("hh \n");

		single_comm = from_list_to_arr(g_struct->tlist); // this arr howa li aydkhl l function
		builtins(g_struct, env, single_comm);
		if (ft_strcmp(single_comm[0], "cd") != 0 && ft_strcmp(single_comm[0], "export") != 0 && ft_strcmp(single_comm[0], "env") != 0 && ft_strcmp(single_comm[0], "pwd") != 0 && ft_strcmp(single_comm[0], "echo") != 0 && ft_strcmp(single_comm[0], "unset") != 0 && ft_strcmp(single_comm[0], "exit") != 0) // temp
		{
			execute_commands(single_comm[0], single_comm, env, g_struct); // hadi hya ki ktexecuti
			update_exit(g_struct);

			add_env_var(&g_struct->envlist, "?", g_struct->exit_arr);
			/* code */
		}
		// printf("1\n");
		free(single_comm);
		// free_tableauv2(hhhh);
		free_tokens(g_struct->tlist); // hadi mzyana ghir ila knt ankhdm b array it needs to go
	}
	// while (1){

	// }
	// print_tokens(g_struct->tlist);
	// free_tokens(g_struct->tlist); // hadi mzyana ghir ila knt ankhdm b array it needs to go
}

int command_id(t_tlist *head)
{
	t_tlist *current = head;

	while (current != NULL)
	{
		/* code */
		if (current->value == PIPE)
			return PIPE;
		if (current->value == REDIW)
			return REDIW;
		if (current->value == REDIR)
			return REDIR;
		if (current->value == APPEND)
			return APPEND;

		current = current->next;
	}

	return 99;
}

void pipes_divider(t_shell *g_struct)
{ // it needs to show 3 3 2
	g_struct->pipes_list = NULL;
	// g_struct->redi_list = NU
	static t_tlist *current;

	current = g_struct->tlist;
	int i = 0;
	int b = 0;
	int a;
	a = element_counter(g_struct->tlist, PIPE) + 1;
	while (i < a)
	{
		b = nodes_count(&current);

		// printf(" hh \n");
		pipes_list(g_struct, b);

		i++;
	}
	if (g_struct->redi_list != NULL)
	{
		t_node *cu;
		cu = g_struct->pipes_list;
		while (cu && cu->next)
		{
			/* code */
			// if(cu->next)
			cu = cu->next;
		}

		// printf("%p %p\n",cu,g_struct->pipes_list);
		cu->redirect = g_struct->redi_list;
		// printf("%s %s %d\n",cu->args[0],cu->redirect->file,cu->redirect->type);
		/* code */
	}
}

// "$USER"
