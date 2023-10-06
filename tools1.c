#include "minishell.h"

bool quotes_errors(char *str)
{

	int i = 0;
	bool s_q = true;
	bool d_q = true;

	while (str[i])
	{
		if (str[i] == '\"' && s_q == true)
		{
			d_q = !d_q;
			/* code */
		}
		else if (str[i] == '\'' && d_q == true)
		{
			s_q = !s_q;
		}

		i++;
	}
	return (s_q && d_q);
}
bool list_check(t_tlist *head)
{

	t_tlist *current = head;
	while (current != NULL)
	{
		if (quotes_errors(current->str) == false)
			return (false);
		if(current->value == PIPE && current->queue == 0)
			return (false);
		// if((|| current->value == PIPE) && (current->next->value != WORD ||current->next->value != OPT ))
		// return (false);
			// printf("1\n");
		if ((current->value == APPEND || current->value == REDIR || current->value == REDIW || current->value == DOC|| current->value == PIPE) && !current->next)
		{
		return (false);
		}
		// {
			// printf("2\n");
		if((current->value == REDIR || current->value == REDIW || current->value == PIPE) && (current->next->value != WORD && current->next->value != OPT && current->next->value != QUOTES && current->next->value != EXPAND))
		{
			// printf("%d %d \n",current->next->value,current->value);

			return (false);
		}
			// printf("3\n");
		if ((current->value == APPEND || current->value == REDIR || current->value == REDIW || current->value == DOC) && current->next == NULL  )
		{

			return (false);
		}
		// if ()
		current = current->next;
		/* code */
	}
	return true;
}

char *delete_pos(char *str, int pos)
{

	int i = 0;
	int j = 0;
	char *result;
	result = malloc(ft_strlen(str));

	while (str[i])
	{
		// printf(".%s.\n",result);
		if (j == pos)
		{
			i++;
			// continue;
			/* code */
		}
		result[j] = str[i];
		j++;
		i++;
		/* code */
	}
	result[j] = '\0';
	free(str);
	return (result);
}

char * extract_from_in_list(t_shell * g_struct ,t_var_t *tlist, char * key){

	t_var_t *current ;
	current = tlist;
	int checked = 0;
	while (current)
	{
		if (ft_strcmp(current->key , key) == 0) // here
		{
			return(current->value);
			/* code */
		}
		checked++;
		if (checked == g_struct->count)
		{ // anbdl random i'm here , fix the position $path katmchi
			return ("");
		}

		
		current = current->next;
		/* code */
	}
	return("");
}
char *strdelch(char *str, char ch)
{
	char *current = str;
	char *tail = str;

	while (*tail)
	{
		if (*tail == ch)
		{
			tail++;
		}
		else
		{
			*current++ = *tail++;
		}
	}
	*current = 0;
	return str;
}