#ifndef MINISHELL_H
#define MINISHELL_H
#include "./gnl/get_next_line.h"
#include "./libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

// int g_grlobal;
// enum tokens
// {

// };

typedef struct s_prompt
{
    char * command;
    char * cmd;
    char **flags;
    char **tempdevider;
    int twodlen;

} t_prompt;

typedef struct s_counter
{

int quotes;
int d_quotes;
int pipes;
int r_left;
int r_right;


}t_counter;
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
void element_init(t_counter *elements,char *str);
int syntax_check(t_counter *elements,char *str);
/*	----	----utils----	-----	*/
int e_search(char* str, char c);
char *quotefixer(char *str, char quote);
int closed_quotes(char *str);
int closed_double_quotes(char *str);
char* code_3_quotes(char * str);
char *special_trim(char * str, char c);
char *simple_trim(char *str, char c);
void the_divider(t_prompt *helper ,t_counter *elements, char *str);
int twodlen(char **tableau);
void quoter(t_prompt *helper);
void str_replacement(char *str);
// void strr_replacement(char *str);
/*	----	----temp----	-----	*/
int isQuotesClosed(const char *str);
/*	----	----free----	-----	*/
void free_tableau(char** tableau,int lines);

#endif