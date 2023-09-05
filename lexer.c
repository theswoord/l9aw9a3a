#include "minishell.h"


void tokenisation(char * str)
{

    char **done = ft_strsplit(str); // pit eveyone in a node

	add_token_list(&g_struct.tlist,done);
	
	free_tableau(done, twodlen(done));


	// modify_env(g_struct.tlist,g_struct.envlist);

	// print_env(g_struct.envlist,0);

	//modify manually
	// printf("-------------------------------------------------------------------------------\n");
	// add_env_var(&g_struct.envlist,"nabilhhehehehehewiloooo","500 mlyoun");
	printf("_%d_\n", g_struct.count);
	modify_env(g_struct.tlist); // = makaynach o makayzidch token okhra
	printf("_%d_\n", g_struct.count);

	expander_init(g_struct.tlist,NULL);

	// add_env_var(&g_struct.envlist,g_struct.tlist->str,"99");
	// add_env_var(&g_struct.envlist,"nakbst","500 mlyoun");
	// add_env_var(&g_struct.envlist,"nabilhgdfgmlmimi","500 mlyoun");


	// print_env(g_struct.envlist,0);

	print_tokens(g_struct.tlist);
	if (ft_strcmp(str,"env")==0)
	print_env(g_struct.envlist,0);
    // int i = 0;

    // while (done[i])
    // {
    //     printf("arr[%d] = %s\n",i,done[i]);
    //     i++;
    //     /* code */
    // }
	// // printf("thankyouuuu \n");
	// // t_tlist *current;
	// // current = g_struct.tlist;
	// printf("node 1 = %s\n",g_struct.tlist->str);
	// printf("node 2 = %s\n",g_struct.tlist->next->str);
	// printf("node 3 = %s\n",g_struct.tlist->next->next->str);
	// printf("node 4 = %s\n",g_struct.tlist->next->next->next->str);

    // while (current != NULL)
	// {
	// 	printf("%s %d\n",current->str , current->value);
	// 	/* code */
	// 	current = g_struct.tlist->next;
	// }
	

}
void modify_env(t_tlist *token){

	t_tlist *tmp = token;
	// t_var_t *currentenv = *env;
	char *key;
	char *value;
	while (tmp != NULL)
	{
		if(tmp->value == VAR)
		{
		key = ft_substr(tmp->str, 0, ft_charfind(tmp->str, '='));
		value = ft_strchr(tmp->str, '=') + 1;
		if(add_env_var(&g_struct.envlist,key,value))
		g_struct.count++; //blati nbdl lik blassa
		free(key);
		}
		tmp = tmp->next;
	}
	
}
void expander_init(t_tlist *head, t_var_t *env){

	t_tlist *tmp = head;
	int i = 0;
	int DQ = 0;
	while (tmp != NULL) //define type dial expantion /li deja kayna b7al PATH o dakchi 
	{
		// if (tmp->value == EXPAND) // checks if the $is inside oula outside o wach kayn f env oula la also wach real oula la
		// {
		// 	while (tmp->str[i])
		// 	{
		// 		if(tmp->str[i] == '\"' && DQ == 0)
		// 		{
		// 			DQ = 1;
		// 			i++;
		// 		}
		// 		if (tmp->str[i] == '$')
		// 		{
		// 			/* code */
		// 		}
				
		// 		i++;
		// 	}
			
			if (tmp->value == EXPAND)
			{
				tmp->str = expanded(tmp->str);
				// while (tmp->str[i]) // substr mn $ tal 7ed ' '
				// {

				// 	/* code */

				// }
				
				/* code */
			}
			
			
		// }
		tmp = tmp->next;
	}
	
}
char * expanded(char* str){

	t_var_t *tmp;
	tmp = g_struct.envlist;
	char *first;
	char *later;
	char *expantion;
	int checked = 0;
	first = ft_substr(str,0,pos(str,'$'));
	later = ft_strchr(str,'$')+1;
	while (tmp != NULL) // ila mal9itoch dir fih NULL
	{



		if(ft_strcmp(tmp->key,later)==0)
		{
			
			expantion = ft_strdup(tmp->value);
			return(ft_strjoingnl(first,expantion));
		}
		checked ++;
		if (checked == g_struct.count) // i'm here , fix the position $path katmchi
		expantion = ft_strdup("");
		/* code */
		tmp = tmp->next;
	}
	return ft_strjoingnl(first,expantion);

	// free(first);
	
}
static int	skip_sep(char *s)
{
	int		i;
	int		opmax;
	int		counter;
	char	quotation_type;

	i = 0;
	quotation_type = s[i];
	opmax = 2;
	counter = 0;
	// if (s[i] == '(' || s[i] == ')')
	// 	opmax = 1;
	while (s[i] == quotation_type && s[i] != '\0' && counter++ < opmax)
		i++;
	return (i);
}

static int	ft_word_len(char *s)
{
	char	quotation_type;
	int		i;

	i = 0;
	if (s[i] == '>' || s[i] == '<'
		|| s[i] == '|')
		i += skip_sep(s);
	else
	{
		while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0'
			&& s[i] != '>' && s[i] != '<'
			&& s[i] != '|' )
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				quotation_type = s[i++];
				while (s[i] != quotation_type && s[i] != '\0')
					i++;
			}
			i++;
		}
	}
	return (i);
}

// ft_count - counts how many words are in the string given
// DESCRIPTION : 
//// the function starts by loopping through a string
//// then skips any tab or space using a loop
//// checks if the string doesnt only contain spaces 
static int	ft_count(char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] != '\0')
			count++;
		i += ft_word_len(&s[i]);
	}
	return (count);
}

// ft_strsplit - splits a string based on spaces and tabs or special chars 
// special chars >, <, &, |, ",'
char	**ft_strsplit(char *s)
{
	char	**splitted ;
	int		splitted_iterator;
	int		i;
	int		word_len;

	splitted = (char **) ft_calloc((ft_count(s) + 1), sizeof(char *));
	i = 0;
	splitted_iterator = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == ' ' || s[i] == '\t') && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		word_len = ft_word_len(&s[i]);
		splitted[splitted_iterator] = (char *) malloc(word_len + 1);
		ft_strlcpy(splitted[splitted_iterator++], &s[i], word_len + 1);
		i += word_len;
	}
	return (splitted);
}