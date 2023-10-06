#include "minishell.h"

void free_pipes(t_node *head){

	t_node *current;
	t_node *temp;
	current = head;
		// printf("%d\n",current->total);

	while (current->next != NULL)
	{
		temp = current;
		// printf("%d\n",temp->total);
		current = current->next;
		// free_tableau(temp->args,temp->total);
		/* code */
		free_tableauv2(temp->args);
		// free(temp->redirect);
		// temp = NULL;
		free(temp);


	}
	free(current);


}
void free_tokens(t_tlist *head)
{

	t_tlist *current;
	t_tlist *temp;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->str);
		free(temp);
		// free(temp)
		/* code */
	}
}
int typefinder(char *line)
{
	int i =0;
	// printf("%s\n",line);
	while (line[i])
	{
		// printf("[%c ]\n",line[i]);
		if(line[i] == '$')
		return(EXPAND);
		else if(line[i] == '<' && line[i+1] == '<')
		return(DOC);
		else if (line[i] == '>' && line[i+1] == '>')
		return(APPEND);
		else if (line[i] == '<' && line[i+1] != '<')
		return(REDIR);
		else if (line[i] == '-' && ft_isprint(line[i+1]) == 1)
		return(OPT);
		else if (line[i] == '|')
		return(PIPE);
		else if (line[i] == '>')
		return(REDIW);
		else if (line[i] == '=' && line[i-1])
		return(VAR);
		else if (line[i]== '\'' || line[i]== '\"')
		return(QUOTES);
		i++;
	}
		return(WORD);
	


	// if (ft_strchr(line, '|'))
	// {
	// 	// g_struct.tlist->value = PIPE;
	// 	return (PIPE);
	// 	/* code */
	// }

	// if (ft_strchr(line,'$'))
	// {
	// 	return (EXPAND);
	// }
	// return (WORD);
}
int find_in_list(t_var_t *head, char* search){

	t_var_t *current;
	current = head;
	while (current != NULL)
	{
		if(ft_strcmp(current->key,search) == 0)
			return 1;
		current = current->next;
	}
	return 0;
}
void print_tokens(t_tlist *head){
	t_tlist *current = head;

	while (current != NULL)
	{
		
		printf("%s %d %d\n", current->str,current->value,current->queue);
		current = current->next;
		/* code */
	}
	
}
