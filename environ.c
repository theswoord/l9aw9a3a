#include "minishell.h"

char *add_exit_to_env(t_shell * g_struct, int exit){


	if (g_struct->exit_arr)
	{
		free(g_struct->exit_arr);
		/* code */
	}
	else
	{
		return(ft_itoa(g_struct->exit_status)) ;
	}
	return NULL;
}
void update_exit(t_shell *g_struct){

	static int i = 0;
	// if (g_struct->exit_arr)
	// {
	// 	printf("3iw\n");
	// 	free(g_struct->exit_arr);
	// 	/* code */
	// }
	if (i != 0)
	{
		free(g_struct->exit_arr);
	}
	g_struct->exit_arr = ft_itoa(g_struct->exit_status);
	add_env_var(&g_struct->envlist,"?",g_struct->exit_arr);
		// printf("%p\n",g_struct->exit_arr);
	i++;
}
void modify_env(t_shell *g_struct, t_tlist *token)
{

	t_tlist *tmp = token;
	// t_var_t *currentenv = *env;
	char *key;
	char *value;
	while (tmp != NULL)
	{
		if (tmp->value == VAR) // here gad lyosawi ikoun flwl
		{
			key = ft_substr(tmp->str, 0, ft_charfind(tmp->str, '='));
			value = ft_strchr(tmp->str, '=') + 1;
			if (add_env_var(&g_struct->envlist, key, value))
				g_struct->count++; // blati nbdl lik blassa
			free(key);
		}
		tmp = tmp->next;
	}
}