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
typedef struct s_list{

    int value;
    char *str;
    struct s_list* next;

}t_list;


typedef struct s_tree {
    char* data;
    struct s_tree* left;
    struct s_tree* right;
}t_tree;

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
// 	struct s_tre	*left;
// 	struct s_tre	*right;
// 	struct s_tre	*parent;

// }t_tre;

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
// int quotation(char *str,int c);
void linkwithex(char **tableau);
char* ft_strtok(char **str);
// void strr_replacement(char *str);
/*	----	----temp----	-----	*/
int isQuotesClosed(const char *str);
/*	----	----free----	-----	*/
void free_tableau(char** tableau,int lines);
/*	----	----print----	-----	*/
void printTree(struct s_tree* root);
void printInOrderIndented(struct s_tree* node, int depth);
void printBinaryTree(struct s_tree* root, int level, char direction);
void printSpaces(int count);
/*	----	----tree----	-----	*/
void insertNode(struct s_tree** root, char* data);
void freeTree(struct s_tree* node);
/*  ----    ----list----    -----   */
t_list *l_addnode(char* data);
int list_size(t_list *head);
void l_addback(t_list*list,char *data);
void l_print(t_list *list);
t_list *create_node(char* s);
void add_list(t_list **head,char *s);
char	*ft_substrmini(char *s, unsigned int start, size_t len);
#endif