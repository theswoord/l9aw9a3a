#include "minishell.h"

char *quotes_moncef(char *str)
{

	int i = 0;
	int j = 0;
	bool s_q = true;
	bool d_q = true;
	char *result;
	result = ft_calloc(ft_strlen(str), 1);
	while (str[i])
	{
		if (str[i] == '\"' && s_q == true)
		{
			// printf("fdgdfg\n");
			d_q = !d_q;
			while (str[i] == '\"')
			{
			i++;
				/* code */
			}
			
			// printf("%c\n",str[i]);
			// check = true;
			/* code */
		}
		else if (str[i] == '\'' && d_q == true)
		{
			s_q = !s_q;
			while (str[i] == '\'')
			{
			i++;
				/* code */
			}
			// check = true;
		}

		result[j] = str[i];
		j++;
		i++;
		// printf("%d %d %s\n",i,j,result);
	}

	free(str);
	return (result);
}









char *expander_qv2(t_shell *g_struct, char *str)
{
   
	 int i =0;
	int j = 0;
	int k = 0;
	char *request = NULL;
	char *expantion = NULL;
	char *out = ft_calloc(ft_strlen(str)+1,1);
	while(str[i]){
		// printf("hhhhhh\n");
		if (str[i] == '$'){
			i++;
			j=i;
			while (ft_isalnum(str[i]) == 1 || str[i] == '?' )
				i++;
			request = ft_substr(str, j, i - j);
			expantion = env_expander(g_struct,g_struct->envlist,request);
			out = ft_strjoingnl(out, expantion);
			out = ft_realloc(out , (ft_strlen(str)+ft_strlen(expantion)));
			k += ft_strlen(expantion);
			free(expantion);
		}
		else
		{
			out[k]=str[i];
			out[k+1]='\0';
			k++;
			i++;
		}
	}
	free(str);
	return out;
}

void builtins(t_shell *g_struct , char ** env ,  char ** single_comm){
		if(ft_strcmp(single_comm[0],"cd") == 0)
	{
		cd_command(single_comm[1],env,g_struct);
		update_exit(g_struct);
		// add_env_var(&g_struct->envlist,"?",g_struct->exit_arr);

	}
	else if (ft_strcmp(single_comm[0],"env") == 0)
	{
		// print_env(g_struct->envlist,0);
		ft_env(g_struct,twodlen(single_comm),single_comm);
		update_exit(g_struct);
		// add_env_var(&g_struct->envlist,"?",g_struct->exit_arr);


	}
	else if (ft_strcmp(single_comm[0],"export") == 0)
	{
		if (twodlen(single_comm)==1)
		print_env(g_struct->envlist, 1);
		
		export(g_struct,twodlen(single_comm),single_comm,env);
		update_exit(g_struct);
		// add_env_var(&g_struct->envlist,"?",g_struct->exit_arr);


	}
	else if (ft_strcmp(single_comm[0],"unset") == 0)
	{
		// if (twodlen(single_comm)==1)
		// print_env(g_struct->envlist, 1);
		ft_unset(twodlen(single_comm),single_comm,g_struct);
		// export(g_struct,twodlen(single_comm),single_comm,env);
		update_exit(g_struct);
		// add_env_var(&g_struct->envlist,"?",g_struct->exit_arr);


	}
		else if (ft_strcmp(single_comm[0],"exit") == 0)
	{
		ft_exit(single_comm,g_struct);
		update_exit(g_struct);
		// add_env_var(&g_struct->envlist,"?",g_struct->exit_arr);

	}
		else if (ft_strcmp(single_comm[0],"pwd") == 0)
	{
		pwd_command(g_struct);
		update_exit(g_struct);
		// add_env_var(&g_struct->envlist,"?",g_struct->exit_arr);

	}
			else if (ft_strcmp(single_comm[0],"echo") == 0)
	{
		echo_command(twodlen(single_comm),single_comm,g_struct);
		// printf("raw = |%d|\n", g_struct->exit_status);
		update_exit(g_struct);
		// add_env_var(&g_struct->envlist,"?",g_struct->exit_arr);

	}
}


int	allspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}