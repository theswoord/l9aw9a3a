#include "minishell.h"

void builtins(t_shell *g_struct , char ** env ,  char ** single_comm){
		if(ft_strcmp(single_comm[0],"cd") == 0)
	{
		cd_command(single_comm[1],env,g_struct);
		add_env_var(&g_struct->envlist,"?",ft_itoa(g_struct->exit_status));

	}
	else if (ft_strcmp(single_comm[0],"env") == 0)
	{
		// print_env(g_struct->envlist,0);
		ft_env(g_struct,twodlen(single_comm),single_comm);
		add_env_var(&g_struct->envlist,"?",ft_itoa(g_struct->exit_status));


	}
	else if (ft_strcmp(single_comm[0],"export") == 0)
	{
		if (twodlen(single_comm)==1)
		print_env(g_struct->envlist, 1);
		
		export(g_struct,twodlen(single_comm),single_comm,env);
		add_env_var(&g_struct->envlist,"?",ft_itoa(g_struct->exit_status));


	}
	else if (ft_strcmp(single_comm[0],"unset") == 0)
	{
		// if (twodlen(single_comm)==1)
		// print_env(g_struct->envlist, 1);
		ft_unset(twodlen(single_comm),single_comm,g_struct);
		// export(g_struct,twodlen(single_comm),single_comm,env);
		add_env_var(&g_struct->envlist,"?",ft_itoa(g_struct->exit_status));


	}
		else if (ft_strcmp(single_comm[0],"exit") == 0)
	{
		ft_exit(single_comm,g_struct);
		add_env_var(&g_struct->envlist,"?",ft_itoa(g_struct->exit_status));

	}
		else if (ft_strcmp(single_comm[0],"pwd") == 0)
	{
		pwd_command(g_struct);
		add_env_var(&g_struct->envlist,"?",ft_itoa(g_struct->exit_status));

	}
			else if (ft_strcmp(single_comm[0],"echo") == 0)
	{
		echo_command(twodlen(single_comm),single_comm,g_struct);
		add_env_var(&g_struct->envlist,"?",ft_itoa(g_struct->exit_status));

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

void tokenisation(char *str, t_shell *g_struct, char **env)
{

	if (allspaces(str) == 1 || ft_strlen(str) == 0)
	{
		return;
		/* code */
	}
	
	char **done = ft_strsplit(str); // pit eveyone in a node

	add_token_list(&g_struct->tlist, done);

	free_tableau(done, twodlen(done));

	modify_env(g_struct, g_struct->tlist); // lmochkil ila kan chi 7aja wst param it's not it
	
	expander_init(g_struct, g_struct->tlist, NULL);
	// hadchi khdam
	// exit_status_error(g_struct,0);
	if (list_check(g_struct->tlist))
	{
		qidentify(g_struct, g_struct->tlist); // here nonini nonini moraja3a H rj3o a nabil
											  // print_tokens(g_struct->tlist);
	}
	else{
		g_struct->exit_status = 258;
		// printf("%d\n ",g_struct->exit_status);
		add_env_var(&g_struct->envlist,"?",ft_itoa(g_struct->exit_status));
		printf("minishell: syntax error\n");
		return;
	}
	// printf("hh\n");
	
		char **single_comm;								 // hadi kmala
		single_comm = from_list_to_arr(g_struct->tlist); // this arr howa li aydkhl l function
	// if ()
	// {
	// 	/* code */
	// }
	// cd_command()

	// if ()
	builtins(g_struct,env,single_comm);

	// printf("hhhghghghg\n");

	if (command_id(g_struct->tlist) == PIPE ||command_id(g_struct->tlist) == REDIW || command_id(g_struct->tlist) == REDIR || command_id(g_struct->tlist) == APPEND)
	{
		files_finder(g_struct->tlist);
		// printf(" zqqq\n");
		redi_set(g_struct);
		pipes_divider(g_struct);
		// print_pointers2(g_struct->redi_list);
		// printf("arg = %s point redi = %p file = %s type = %d \n",g_struct->pipes_list->args[1],g_struct->pipes_list->redirect,g_struct->pipes_list->redirect->file,g_struct->pipes_list->redirect->type);
		// printf("%s  %d %s\n",g_struct->redi_list->file,g_struct->redi_list->type,g_struct->redi_list->next->next->file);
		
		// printf(" %p |%s|\n",g_struct->pipes_list->redirect->file,g_struct->pipes_list->redirect->file);
		execute_pipelines(&g_struct->pipes_list, env,g_struct);
		add_env_var(&g_struct->envlist,"?",ft_itoa(g_struct->exit_status));
		g_struct->redi_list = NULL;

	}
	else if (command_id(g_struct->tlist) == PIPE)
	{
		pipes_divider(g_struct);
		execute_pipelines(&g_struct->pipes_list, env,g_struct);
		add_env_var(&g_struct->envlist,"?",ft_itoa(g_struct->exit_status));

	}
	else
	{
		// char **single_comm;								 // hadi kmala
		// single_comm = from_list_to_arr(g_struct->tlist); // this arr howa li aydkhl l function
		if (ft_strcmp(single_comm[0],"cd") != 0 && ft_strcmp(single_comm[0],"export") != 0 && ft_strcmp(single_comm[0],"env") != 0 && ft_strcmp(single_comm[0],"pwd") != 0 && ft_strcmp(single_comm[0],"echo") != 0&& ft_strcmp(single_comm[0],"unset") != 0&& ft_strcmp(single_comm[0],"exit") != 0) // temp
		{
		execute_commands(single_comm[0], single_comm, env, g_struct); // hadi hya ki ktexecuti
		add_env_var(&g_struct->envlist,"?",ft_itoa(g_struct->exit_status));
			/* code */
		}
		
		free(single_comm);
		// free_tableauv2(hhhh);
	free_tokens(g_struct->tlist); // hadi mzyana ghir ila knt ankhdm b array it needs to go
	}
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
int element_counter(t_tlist *head, int what)
{
	int count = 0;
	t_tlist *current = head;

	while (current != NULL)
	{
		if (current->value == what)
		{
			count++;
		}

		current = current->next;
	}
	return count;
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

void print_pointers2(t_redi_node* head){
	t_redi_node* current;
	current = head;
	while (current != NULL)
	{
		printf ("ptr |%p| strptr |%p| \n",current,current->file);
		current = current->next;
		/* code */
	}
	
}
void print_pointers(t_tlist *head){
	t_tlist *current;
	current = head;
	while (current != NULL)
	{
		printf ("ptr |%p| str |%s| strptr |%p| \n",current,current->str,current->str);
		current = current->next;
		/* code */
	}
	
}
void special_free(t_shell *g_struct) {
	t_tlist *current;
	current = g_struct->tlist;
	while (current != NULL) {
    if (current->str) {
        free(current->str);
    }
    
    if (current->next) {
        free(current->next->str);
        free(current->next);
    }
    
    free(current);
    current = NULL; // Set to NULL to indicate that the memory has been freed
}
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
char *quotes_moncef(char *str)
{

	int i = 0;
	int j = 0;
	bool s_q = true;
	bool d_q = true;
	char *result;
	result = ft_calloc(ft_strlen(str) - 1, 1);
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

		result[j] = str[i];
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
			// if (pos(tmp->str, '\'') != -1) // had l3jb makhdamch
			// {
			// 	// only remove
			// 	// tmp->str = strdelch(tmp->str, '\'');
			// 	// printf("ided\n");
			// 	// ft_memmove(&tmp->str[0], &tmp->str[0 + 1], ft_strlen(tmp->str) - 1);
			// 	// if (ft_strlen(tmp->str) < 2) {
			// 	// *tmp->str = '\0';
			// 	// } else {
			// 	// ft_memmove(tmp->str, tmp->str + 1, ft_strlen(tmp->str) - 2);
			// 	// tmp->str[ft_strlen(tmp->str) - 2] = '\0';
			// 	// }
			// 	/* code */
			// }

			 if (pos(tmp->str, '\"') != -1)
			{
				// printf("idad\n");
				if (pos(tmp->str, '$') != -1)
				{
					// printf("b4 = |%s\n",tmp->str);
					// free(tmp->str);
					tmp->str = expander_qv2(g_struct, tmp->str); // try this first mn '"to $' dollars '$PATH $USER' mn $tal ' ' later mn ' ' tal " oula ghir tal "
					// printf("wst loop =%s\n",tmp->str);
					// tmp->str = expander_qv2(g_struct, &tmp->str); // try this first mn '"to $' dollars '$PATH $USER' mn $tal ' ' later mn ' ' tal " oula ghir tal "

				
					// printf("%s\n", tmp->str);
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
	while (tmp != NULL) 
	{

		if (tmp->value == EXPAND)
		{
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
		arr[i] = current->str;
		// free(current->str);
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
char *ft_realloc(char* str, int size){


if (str == NULL) {
        return ft_calloc(size,1);
    } else if (size == 0) {
        // If the size is 0, it's equivalent to calling free(ptr)
        free(str);
        return NULL;
    } else {
	char* tmp ; 
	int old_size = ft_strlen(str)+1;

	tmp = ft_calloc(size,1);

	ft_strlcpy(tmp,str,old_size);
	free(str);
	return tmp;
}

}
char *expander_qv2(t_shell *g_struct, char *str)
{
    // int i = 0;
    // int j = 0;
    // char *first = NULL;
	// first = ft_substr(str, 0, pos(str, '$'));
    // char *exp = NULL;
    // char *req = NULL;
	// char *test =NULL;
    // char *out = malloc(1);
	// int p = 0;
    // while (str[i])
    // {
    //     if (str[i] == '$')
    //     {
    //         i++;
    //         j = i;
    //         while (ft_isalnum(str[i]) == 1 && (str[i] != '\'' || str[i] != '\"'))
    //         {
    //             i++;
    //         }
    //         req = ft_substr(str, j, i - j);
	// 		// printf("req %p\n",req);
    //         exp = env_expander(g_struct, g_struct->envlist, req);
	// 		// printf("exp %p\n",exp);
	// 		if (p == 0)
	// 		{
    //         out = ft_strjoingnl(first, exp);
	// 		p = 1;
	// 		// free(req);
    //         // free(exp);
	// 		continue;
	// 		}
    //         out = ft_strjoingnl(out, exp);
    //         // free(req);
    //         free(exp);
    //     }
    //     else
    //     {
	// 		// test = ;
    //         out = ft_strjoin(out, ft_substr(str, i, 1));
	// 		printf("test= |%s| = %p out= |%s| = %p \n",test,test,out,out);
	// 		// free(test);
    //         i++;
    //     }
    // }
	// // printf("%p %p %p\n",req,out,first);
    // free(first);

    // return out;
	 int i =0;
	int j = 0;
	int k = 0;
	// char *first = ft_substr(str, 0, pos(str, '$'));
	char *request = NULL;
	char *expantion = NULL;
	char *out = ft_calloc(ft_strlen(str)+1,1);
			// printf("|%s|\n", out);
	// printf ("ana size  : %zu\n", ft_strlen (str));
	while(str[i]){

		if (str[i] == '$'){
			i++;
			j=i;
			while (ft_isalnum(str[i]) == 1 )
			{
				i++;
			
				/* code */
			}
			request = ft_substr(str, j, i - j);
			// printf(">%s<\n",request);
			expantion = env_expander(g_struct,g_struct->envlist,request);
			// printf("|%s|\n",expantion);
			out = ft_strjoingnl(out, expantion);
			// printf("out = %s\n",out);
			// printf("|%s|\n", out);
			// i = 0;
			out = ft_realloc(out , (ft_strlen(str)+ft_strlen(expantion)));
			// printf("after = %s\n",out);
			k += ft_strlen(expantion);
			// i += ft_strlen (out);
			// i--;
		}
		else
		{
			out[k]=str[i];
			out[k+1]='\0';
			k++;
			// printf(".%c.\n", out[i]);
			i++;
		}
		// i++;
	// printf("fiiig after = %s\n",out);
	// printf ("size db : %d \n", i);
	}
	return out;
}

char	*ft_strjoinmini(char *s1, char *s2)
{
	char	*tkhlita;
	int		a;
	int		d;
	int		ls1;
	int		ls2;

	ls1 = ft_strlengnl(s1);
	ls2 = ft_strlengnl(s2);
	a = 0;
	tkhlita = (char *)ft_calloc((ls1 + ls2) + 1, 1);
	if (!tkhlita)
		return (0);
	while (a < ls1)
	{
		tkhlita[a] = s1[a];
		a++;
	}
	d = 0;
	while (d < ls2)
	{
		tkhlita[a++] = s2[d++];
	}
	free(s1);
	free(s2);
	return (tkhlita);
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