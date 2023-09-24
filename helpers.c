#include "minishell.h"

int ft_charfind(const char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (0);
}

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int add_env_var(t_var_t **head, char *key, char *value)
{
	// int success;
	t_var_t *new_node;
	t_var_t *current;

	current = *head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (ft_strcmp(current->value, value) != 0)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			return 0;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_var_t));
	new_node->key = ft_strdup(key);
	if (!value)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = *head;
	*head = new_node;
	return (1);
}

void initialize_environment(t_shell *g_struct,t_var_t **head, char **env)
{
	char *key;
	char *value;
	int i;
	*head = NULL;
	i = 0;
	// printf("fsdfsd\n");
	while (env[i] != NULL)
	{

		if (ft_charfind(env[i], '=') != 0)
		{
			key = ft_substr(env[i], 0, ft_charfind(env[i], '='));
			value = ft_strchr(env[i], '=') + 1;
			add_env_var(head, key, value);
			g_struct->count++;
			free(key);
		}
		i++;
	}
			// printf("+%d\n",g_struct->count);
}

void free_env(t_var_t *head)
{
	t_var_t *current;
	t_var_t *temp;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void print_env(t_var_t *head, int boole)
{
	t_var_t *current = head;

	while (current != NULL)
	{
		if (boole == 1)
		{
			if (!(current->value))
				printf("declare -x %s\n", current->key);
			else
				printf("declare -x %s=\"%s\"\n", current->key, current->value);
		}
		else
		{
			if (!(current->value))
				printf("%s\n", current->key);
			else
				printf("%s=\"%s\"\n", current->key, current->value);
		}
		current = current->next;
	}
}

char *env_nav(t_var_t **head, char *key)
{

	t_var_t *current;
	current = *head;
	char *outsider;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			outsider = ft_strdup(current->value);
		}
		current = current->next;
	}
	return outsider;
}
void token_list(t_tlist **head, char *tok, int type, int queue)
{

	// int i = 0;
	t_tlist *current;
	t_tlist *new_node;
	// static int queue = 0;
	// t_tlist *current = *head;
	current = *head;
	// while (current != NULL)
	// {
	// 	current = current->next;
	// 	/* code */
	// }

	new_node = malloc(sizeof(t_tlist));
	new_node->str = ft_strdup(tok);
	// free(tok);
	if (type)
	new_node->value = type;	
	new_node->queue = queue;
	
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}
void add_token_list(t_tlist **head, char **tab)
{

	int i = 0;
	char *tok;
	char *type;
	*head = NULL;
	// i = twodlen(tab)-1;
	// printf("before %d\n", i);
	while (tab[i] != NULL)
	{
		// if (/* condition */) condition dial word pipe o dakchi
		// {
		// 	/* code */
		// }
		token_list(head, tab[i], typefinder(tab[i]),i); // 7yed had nuull
		i++;
	}
	// printf("after = %d\n", i);
}
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
