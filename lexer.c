#include "minishell.h"

void tokenisation(char *str, t_shell *g_struct, char **env)
{

	char **done = ft_strsplit(str); // pit eveyone in a node

	add_token_list(&g_struct->tlist, done);

	free_tableau(done, twodlen(done));

	// modify_env(g_struct.tlist,g_struct.envlist);

	// print_env(g_struct.envlist,0);

	// modify manually
	//  printf("-------------------------------------------------------------------------------\n");
	//  add_env_var(&g_struct.envlist,"nabilhhehehehehewiloooo","500 mlyoun");
	// printf("_%d_\n", g_struct->count);
	modify_env(g_struct, g_struct->tlist); // lmochkil ila kan chi 7aja wst param it's not it
	// printf("_%d_\n", g_struct->count);
	expander_init(g_struct, g_struct->tlist, NULL);

	if (command_id(g_struct->tlist)== PIPE)
	{
		pipes_divider(g_struct);
		/* code */
	}
	
	// char *test[4];
	// test[0]="ls";
	// test[1]="-l";
	// test[2]="-a";
	// test[3]=NULL;
	// print_tokens(g_struct->tlist);

	// hadchi khdam

	// char **hhhh; // hadi kmala
	// hhhh = from_list_to_arr(g_struct->tlist); // this arr howa li aydkhl l function

	// printf("|%s|\n",hhhh[0]);
	// int j = 0;
	// while (hhhh[j])
	// {
	// 	printf("-%s-\n",hhhh[j]);
	// 	j++;
	// }

	// execute_commands(hhhh[0],hhhh,env); // hadi hya ki ktexecuti

	// hadchi khdam
	// test pipe
	// array_of_commands *command_list;
	// // command_list.num_commands=2;
	// // // command_list.commands[2];
	// // command_list.commands=(command *)malloc(command_list.num_commands*sizeof(command));
	// // command_list.commands[0].command="ls";
	// // command_list.commands[0].args = malloc(1 * sizeof(char*));
	// // // command_list.commands[0].args[0]="ls";

	// // command_list.commands[0].args[0]="-la";
	// // // command_list.commands[0].args[1]="-a";
	// // // command_list.commands.args="-la";
	// // command_list.commands[1].command=malloc(500);
	// // // command_list.commands
	// // command_list.commands[1].command="sort";
	// // command_list.commands[1].args = malloc(100);
	// // command_list.commands[1].args[0]=NULL;
	// // printf("hh\n");
	// command_list = malloc(sizeof(array_of_commands));
	// command_list->num_commands = 2;
	// command_list->commands = (command *)malloc(command_list->num_commands * sizeof(command));

	// command_list->commands[0].command = "ls";
	// command_list->commands[0].args = (char **)malloc(2 * sizeof(char *));
	// // command_list->commands[0].args[0] = "ls";
	// command_list->commands[0].args[0] = "-l";
	// command_list->commands[0].args[1] = NULL;

	// // command_list->commands[1].command = "grep";
	// // command_list->commands[1].args = (char **)malloc(2 * sizeof(char *));
	// // command_list->commands[1].args[0] = "grep";
	// // command_list->commands[1].args[1] = "env";
	// // command_list->commands[1].args[2] = NULL;

	// command_list->commands[1].command = "sort";
	// command_list->commands[1].args = (char **)malloc(1 * sizeof(char *));
	// // command_list->commands[1].args[0] = "sort";
	// command_list->commands[1].args[0] = NULL;

	// // command_list->commands[2].command = "wc";
	// // command_list->commands[2].args = (char **)malloc(3 * sizeof(char *));
	// // command_list->commands[2].args[0] = "wc";
	// // command_list->commands[2].args[1] = "-l";
	// // command_list->commands[2].args[2] = NULL;

	// // command_list.commands[1].args[0]=NULL;

	// execute_pipelines(command_list,env);
	// execute_pipelines()
	// char *test;
	// test = ft_strdup("3ayn 3owda");
	// test = delete_pos(test,pos(test,' '));
	// printf("%s\n",test);
	// add_env_var(&g_struct.envlist,g_struct.tlist->str,"99");
	// add_env_var(&g_struct.envlist,"nakbst","500 mlyoun");
	// add_env_var(&g_struct.envlist,"nabilhgdfgmlmimi","500 mlyoun");

	// print_env(g_struct.envlist,0);
	if (list_check(g_struct->tlist))
	{
		qidentify(g_struct, g_struct->tlist); // here nonini nonini moraja3a H rj3o a nabil
		// print_tokens(g_struct->tlist);
	}
	else
		printf("syntax error \n");
	// if (strcmp(str,"cd"))
	// {
	// 	cd_command()
	// 	/* code */
	// }

	// cd_command(2,"gnl",env,g_struct);

	// execute_commands(hhhh[0],hhhh,env); // hadi hya ki ktexecuti

	// free_tokens(g_struct->tlist); // hadi mzyana ghir ila knt ankhdm b array it needs to go
	// free(str);
	// if (ft_strcmp(str, "env") == 0)
	// print_env(g_struct->envlist, 0);
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
int command_id(t_tlist *head)
{
	t_tlist *current = head;

	while (current != NULL)
	{
		/* code */
		if(current->value == PIPE)
		return PIPE;
		if(current->value == REDIW)
		return REDIW;
		if(current->value == REDIR)
		return REDIR;
		if(current->value == APPEND)
		return APPEND;

		current = current->next;
	}
	
	return 99;
}
int nodes_count(t_tlist **current) {
    int nodes = 0;
    
    while (*current != NULL) {
        
        if ((*current)->value == PIPE) {
            (*current) = (*current)->next;
            // printf("%s\n", (*current)->str);
            return nodes;
        }
        nodes++;
        
        (*current) = (*current)->next;
    }
    
    return nodes;
}
int element_counter(t_tlist * head , int what)
{
int count = 0;
t_tlist *current = head;

while (current != NULL)
{
	/* code */
	if (current->value == what)
	{
		count++;
		/* code */
	}
	

	current = current->next;
}
return count;

}
// void pipes_list(t_shell *g_struct,int count){ fix this it's ez 9lb f dftark uncomment

// int i = 0;
// int j = 0;
// t_tlist *current = g_struct->tlist;
// // while (i < count)
// // {
// 	while (current->queue < count)
// 	{
// 		/* code */
// 		g_struct->pipes_list->args[j] = current->str;

// 		current->next;
// 	}
	
// // g_struct->pipes_list->args[i] = g_struct->tlist->str; 
// // i++;
// 	/* code */
// // }


// }
char** pipes_divider(t_shell *g_struct){ // it needs to show 3 3 2 

	static t_tlist *current;

	current = g_struct->tlist;
	char **out;
	int i = 0;
	// t_node *commandnode;

	// commandnode->args
	// out = (char **)malloc(element_counter(head,PIPE)*sizeof(char *)+1);

	while (i < element_counter(g_struct->tlist,PIPE)+1)
	{
	// commandnode = malloc(sizeof(t_node*));
		pipes_list(g_struct,nodes_count(&current));

		i++;
	}
	
	// out[i]
	// out = 
		// printf("%d\n",nodes_count(&current));
		// printf("%d\n",nodes_count(&current));
		// printf("%d\n",nodes_count(&current));

	// while (current != NULL) // hh
	// {
	// 	/* code */
		

	// 	current = current->next;
	// }
	return out;
}
char *quotes_moncef(char *str)
{

    int i = 0;
	int j = 0;
    bool s_q = true;
    bool d_q = true;
	char *result;
	result = ft_calloc(ft_strlen(str)-1,1);
    while (str[i])
    {
        if (str[i] == '\"' && s_q == true)
        {
            d_q = !d_q;
			i++;
			// check = true;
            /* code */
        }
        else if (str[i] == '\'' && d_q == true)
        {
            s_q = !s_q;
			i++;
			// check = true;
        }
        
		
		result[j]=str[i];
		j++;
        i++;
		// printf("%d %d %s\n",i,j,result);
    }

	free(str);
    return (result);
}
void qidentify(t_shell *g_struct, t_tlist *token)
{

	t_tlist *tmp = token;

	while (tmp != NULL) // lil moraja3a hh
	{
		// printf("+%d \n",ft_charfind(tmp->str,'\"'));
		if (tmp->value == QUOTES)
		{
			if (pos(tmp->str, '\'') != -1) // had l3jb makhdamch
			{
				// only remove
				// tmp->str = strdelch(tmp->str, '\'');
				printf("ided\n");
				// ft_memmove(&tmp->str[0], &tmp->str[0 + 1], ft_strlen(tmp->str) - 1);
				// if (ft_strlen(tmp->str) < 2) {
				// *tmp->str = '\0';
				// } else {
				// ft_memmove(tmp->str, tmp->str + 1, ft_strlen(tmp->str) - 2);
				// tmp->str[ft_strlen(tmp->str) - 2] = '\0';
				// }
				/* code */
			}

			else if (pos(tmp->str, '\"') != -1)
			{
				printf("idad\n");
				if (pos(tmp->str, '$') != -1)
				{
					// printf("b4 = |%s\n",tmp->str);
					// free(tmp->str);
					tmp->str = expanded_q(g_struct, tmp->str); // try this first mn '"to $' dollars '$PATH $USER' mn $tal ' ' later mn ' ' tal " oula ghir tal "
					// printf("a4 = |%s\n",tmp->str);
					/* code */
				}

				// remove quotes hh
				//  find $ then replace and remove
				/* code */
			}
			// printf("|%s|\n",tmp->str);
			tmp->str = quotes_moncef(tmp->str); // NABIL FIX LEAKS O FIX
		}

		tmp = tmp->next;
		/* code */
	}
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
void expander_init(t_shell *g_struct, t_tlist *head, t_var_t *env)
{

	t_tlist *tmp = head;
	int i = 0;
	int DQ = 0;
	while (tmp != NULL) // define type dial expantion /li deja kayna b7al PATH o dakchi
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
			// free(tmp->str);
			tmp->str = expanded(g_struct, tmp->str);
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
		checked++;
		if (checked == g_struct->count)
		{ // anbdl random i'm here , fix the position $path katmchi
			free(str);
			expantion = ft_strdup("");
		}
		/* code */
		tmp = tmp->next;
	}
	free(str);
	return ft_strjoingnl(first, expantion);

	// free(first);
}
static int skip_sep(char *s)
{
	int i;
	int opmax;
	int counter;
	char quotation_type;

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

static int ft_word_len(char *s)
{
	char quotation_type;
	int i;

	i = 0;
	if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		i += skip_sep(s);
	else
	{
		while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0' && s[i] != '>' && s[i] != '<' && s[i] != '|')
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
static int ft_count(char *s)
{
	int i;
	int count;

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
char **ft_strsplit(char *s)
{
	char **splitted;
	int splitted_iterator;
	int i;
	int word_len;

	splitted = (char **)ft_calloc((ft_count(s) + 1), sizeof(char *));
	i = 0;
	splitted_iterator = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == ' ' || s[i] == '\t') && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break;
		word_len = ft_word_len(&s[i]);
		splitted[splitted_iterator] = (char *)malloc(word_len + 1);
		ft_strlcpy(splitted[splitted_iterator++], &s[i], word_len + 1);
		i += word_len;
	}
	return (splitted);
}
int list_size(t_tlist *head)
{

	t_tlist *current = head;
	int size = 0;
	while (current != NULL)
	{
		size++;
		current = current->next;
		/* code */
	}
	return size;
}

char **from_list_to_arr(t_tlist *head)
{

	int i = 0;
	int size;
	size = list_size(head);
	char **arr;
	t_tlist *current = head;
	arr = malloc(size * sizeof(char *) + 1);
	while (current != NULL)
	{
		// arr[i]=malloc()
		// /* code */
		// i++;
		arr[i] = ft_strdup(current->str);
		free(current->str);
		// printf("*%s*\n",arr[i]);
		i++;
		current = current->next;
	}
	arr[i] = NULL;

	return arr;
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
	printf("f= %s\n",first);
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
		if (checked == g_struct->count){ // anbdl random i'm here , fix the position $path katmchi
			expantion = ft_strdup("");
		final = recombinator(first, expantion, rest);
		}

		/* code */
		tmp = tmp->next;
	}
			free(str);

	return final;
}
// "$USER"
char *recombinator(char *first, char *later, char *rest)
{
	char *result;

	result = ft_strjoingnl(first, later);
	result = ft_strjoingnl(result, rest);

	free(later);
	// free(rest);
	return result;
}
char *ft_strchrtill(const char *s, int c, int len)
{
	size_t a;
	char *mbdla;

	a = 0;
	mbdla = (char *)s;
	while (a <= ft_strlen(mbdla))
	{
		if (mbdla[a] == (char)c)
		{
			return (mbdla + a - len);
		}
		a++;
	}
	return (0);
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