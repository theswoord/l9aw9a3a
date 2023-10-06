#include "minishell.h"

void files_finder(t_tlist *head){
	t_tlist *current;

	while (current != NULL && current->next)
	{

		if (current->value == REDIR || current->value == APPEND || current->value == REDIW)
		{
			current->next->value = current->value; // temp
			current->next->is_file = true;
			// current->is_file = false;
			// continue;
			// printf("%d %d\n", current->value, current->next->value);
			/* code */
		}
		if (ft_strcmp(current->str, ">") == 0 ||ft_strcmp(current->str, ">>") == 0 ||ft_strcmp(current->str, "<") == 0)
		{
			current->is_file = false;
		}
			// printf("file finder = |%s| is file ? |%d| \n",current->next->str,current->next->is_file);
		
			
		current = current->next;
		/* code */
	}
	

}

int nodes_count(t_tlist **current)
{
	int nodes = 0;

	while (*current != NULL)
	{

		if ((*current)->value == PIPE || (*current)->value == REDIR ||(*current)->value == REDIW ||(*current)->value == APPEND )
		{
			(*current) = (*current)->next;
			return nodes;
		}
		nodes++;

		(*current) = (*current)->next;
	}

	return nodes;
}
t_tlist *pipes_copy(t_tlist *head, t_tlist *current)
{

	while (current != NULL)
	{

		if (current->value == PIPE)
		{
			current = current->next;
			printf("%s\n", current->str);
			return current; // Return the pointer to the current node
		}

		current = current->next;
	}

	return current; // Return NULL to indicate the end of the list
}


void pipes_list(t_shell *g_struct, int count)
{
	int i = 0;
	int j = count;
	t_tlist *current = g_struct->tlist;
	t_node *node = (t_node *)ft_calloc(1, sizeof(t_node));
	node->next = NULL;
	node->args = ft_calloc((count + 1), sizeof(char *));
	while (i < count)
	{
		node->args[i] = current->str;
		free(current);
		i++;
		current = current->next;
	}
	node->redirect = NULL;
	if (!g_struct->pipes_list)
	{
		g_struct->pipes_list = node;
	// printf("%s\n",current->str);
	}
	else
	{

		t_node *last = g_struct->pipes_list;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = node;
	}
	if (current == NULL)
		return;
	// printf("hh = %s\n", current->str);
	free(current->str);
	free(current);
	g_struct->tlist = current->next;
}
void redi_set(t_shell *g_struct){

	t_tlist *current;

	current = g_struct->tlist;

	while (current != NULL)
	{

		if (current->is_file == true)
		{
			add_redi(&g_struct->redi_list,new_redi(current->str,current->value));
		// printf("%s %d\n",current->str,current->is_file);
			/* code */

			current = current->next;
		}
		else
		current = current->next;

		/* code */
	}
	
}