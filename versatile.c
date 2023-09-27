#include "minishell.h"

void versatile_pipes_list(t_shell *g_struct, int count, bool detected)
{
	int i = 0;
	int j = count;
	t_tlist *current = g_struct->tlist;
	t_node *node = (t_node *)ft_calloc(1, sizeof(t_node));
	node->next = NULL;
	node->args = ft_calloc((count + 1), sizeof(char *));
	printf("hh = %d\n",detected);
	printf("%p %p %s %d\n",current, current->next,current->str,current->is_file);
	while (i < count)
	{
		if (current->is_file == true)
		{

			node->redirect = ft_calloc(1,sizeof(t_redi_node));
			node->redirect->file = ft_strdup(current->str);
			node->redirect->type = current->value; // value atkon wa3ra
			/* code */
		}
		else
		node->args[i] = current->str;

		// else
		// node->redirect = NULL;
		// printf("hh\n");
		// else
		
	// if (current->value == REDIR || current->value == REDIW || current->value == APPEND)
	// {
	// node->redirect = NULL;
	// }
	// else
	// {
	// node->redirect = NULL;
	// }
		free(current);
		i++;
		current = current->next;
	}
	// node->redirect = NULL; // hadi 7iedtha atremplaça 
	if (node->redirect)
	{
		printf("%s\n",node->args[0]);
	printf("%s\n",node->redirect->file);
		/* code */
	}
	
	if (!g_struct->pipes_list)
	{
		g_struct->pipes_list = node;
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
	free(current->str);
	free(current);
	g_struct->tlist = current->next;
}

void versatile_divider(t_shell *g_struct)
{ // it needs to show 3 3 2

	static t_tlist *current;

	current = g_struct->tlist;
	int i = 0;
	int b = 0;
	int a;
	a = versatile_counter(g_struct->tlist);
	// int c = 
	printf("vers = %d \n", a);
	while (i < a)
	{
		b = versatile_nodes_count(&current);
	printf("vers while = %d \n", b);

		versatile_pipes_list(g_struct, b, 1);


		i++;
	}
}
int versatile_counter(t_tlist *head)
{
	int count = 0;
	t_tlist *current = head;
	int available = 0;
	while (current != NULL)
	{
		if (current->value == PIPE )
		{
			count++;
		}
		else if (current->value == REDIR ||current->value == REDIW ||current->value == APPEND)
		{
			available=1;
		}

		current = current->next;
	}
	if(available == 0)
	return (count+1);
	return 1;
}
int versatile_nodes_count(t_tlist **current)
{
	int nodes = 0;

	while (*current != NULL)
	{

		if ((*current)->value == PIPE || (*current)->value == APPEND || (*current)->value == REDIW || (*current)->value == REDIR)
		{
			(*current) = (*current)->next;
			return nodes;
		}
		nodes++;

		(*current) = (*current)->next;
	}

	return nodes;
}