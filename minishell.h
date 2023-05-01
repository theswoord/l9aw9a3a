#ifndef MINISHELL_H
#define MINISHELL_H
#include "./gnl/get_next_line.h"
#include "./libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>

// enum tokens
// {

// };

// typedef struct s_prompt
// {
//     char* command;
//     char * cmd;
//     char **flags;

// } t_prompt;

// typedef struct s_tre
// {
// 	char *token;
// 	char *type;
// 	t_tre	*left;
// 	t_tre	*right;
// 	t_tre	*parent;
// } t_tre;

/*	----	----lexer----	-----	*/
void tokenisation(char *str);
/*	----	----utils----	-----	*/
int e_search(char* str, char c);




#endif