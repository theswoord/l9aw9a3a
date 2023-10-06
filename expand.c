#include "minishell.h"

void qidentify(t_shell *g_struct, t_tlist *token)
{

	t_tlist *tmp = token;

	while (tmp != NULL) // lil moraja3a hh
	{
		if (tmp->value == QUOTES)
		{

			 if (pos(tmp->str, '\"') != -1)
			{
				if (pos(tmp->str, '$') != -1)
				tmp->str = expander_qv2(g_struct, tmp->str); // try this first mn '"to $' dollars '$PATH $USER' mn $tal ' ' later mn ' ' tal " oula ghir tal "
			}
			tmp->str = quotes_moncef(tmp->str); // NABIL FIX LEAKS O FIX
		}

		tmp = tmp->next;
		/* code */
	}
}
void expander_init(t_shell *g_struct, t_tlist *head, t_var_t *env)
{

	t_tlist *tmp = head;
	int i = 0;
	int DQ = 0;
	while (tmp != NULL) 
	{

		if (tmp->value == EXPAND)
		{
		// printf("hhh11111111h\n");
			tmp->str = expanded(g_struct, tmp->str);
			// printf("f expander = %s\n", tmp->str);
		}

		tmp = tmp->next;
	}
}
char *expanded(t_shell *g_struct, char *str)
{

	t_var_t *tmp;
	tmp = g_struct->envlist;
	char *first;
	char *later;
	char *expantion;
	int checked = 0;
	first = ft_substr(str, 0, pos(str, '$'));
	// printf("f= %s\n",first);
	later = ft_strchr(str, '$') + 1;
	// printf("l= %s\n",later);

	while (tmp != NULL) // ila mal9itoch dir fih NULL
	{

		if (ft_strcmp(tmp->key, later) == 0)
		{

			expantion = ft_strdup(tmp->value);
			free(str);
			str = ft_strjoingnl(first, expantion);
			return (free(expantion), str);
		}
		// checked++;
		// if (checked == g_struct->count)
		// { // anbdl random i'm here , fix the position $path katmchi
		// 	free(str);
		// 	expantion = ft_strdup("");
		// }
		/* code */
		tmp = tmp->next;
	}
	free(str);
	return ft_strjoingnl(first, "");

	// free(first);
}
char *expanded_q(t_shell *g_struct, char *str)
{

	t_var_t *tmp;
	tmp = g_struct->envlist;
	char *first;
	char *later;
	char *expantion;
	// char *test = malloc(500);
	int checked = 0;

	first = ft_substr(str, 0, pos(str, '$')); // malloced
	// printf("f= %s\n", first);
	later = ft_strchr(str, '$') + 1; // NM
	char *rest;
	rest = ft_strrchr(str, '"'); // NM
	char *final;
	// later = ft_substr(str,pos(str, '$'),pos(str, '\"')-1);
	// printf("l= %s\n",later);

	while (tmp != NULL) // ila mal9itoch dir fih NULL
	{

		// printf("%s\n", ft_strnstr(tmp->key,later,ft_strlen(later)-1));
		// test=ft_strnstr(tmp->key,"USER\"",4);
		// printf("%s\n",test);
		if (ft_strncmp(tmp->key, later, pos(later, ' ')) == 0)
		{
			expantion = ft_strdup(tmp->value);
			final = recombinator(first, expantion, rest);
			// free(first);
			// free(expantion);
			// free(rest);
			free(str);
			return (final);
		}
		checked++;
		if (checked == g_struct->count)
		{ // anbdl random i'm here , fix the position $path katmchi
			expantion = ft_strdup("");
			final = recombinator(first, expantion, rest);
		}

		/* code */
		tmp = tmp->next;
	}
	free(str);

	return final;
}
char *env_expander(t_shell * g_struct,t_var_t *head, char * key){

	t_var_t *current;
	current = head;
	int checked = 0;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key)==0)
		{
		// printf(".%s.%s\n",key,current->value);
			free(key);
			return(ft_strdup(current->value));
		}
		// checked++;
		// if (checked == g_struct->count)
		// {
		// 	free(key);
		// 	return(ft_strdup(""));
		// }

		current = current->next;
		/* code */
	}
	return (free(key), ft_strdup(""));
}