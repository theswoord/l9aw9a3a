#ifndef MINISHELL_H
#define MINISHELL_H
#include "./gnl/get_next_line.h"
#include "./libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

// #define PIPE = 5
// int g_grlobal;
// enum tokens
// {

// };

typedef enum{

PIPE,
REDIW,
REDIR,
WORD,
OPT,
DOC,
EXPAND,
VAR,
APPEND,
QUOTES,
SQUOTE,
DQUOTE,
}e_tokenum;

 typedef struct env_vars
{
	char *key;
	char *value;
	struct env_vars *next;
} t_var_t;


typedef struct s_tlist{

    int value;
    char *str;
    struct s_tlist* next;

}t_tlist;


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

typedef struct s_shell
{

    t_tlist *tlist;
    t_var_t *envlist;
    e_tokenum tokenum;
    int count; // hada test o safi

}t_shell; 

extern t_shell	g_struct;
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
char* ft_strtok(char *str);
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
// t_list *l_addnode(char* data);
// int list_size(t_list *head);
// void l_addback(t_list*list,char *data);
// void l_print(t_list *list);
// t_list *create_node(char* s);
// void add_list(t_list **head,char *s);
char	*ft_substrmini(char *s, unsigned int start, size_t len);
char *toktok(char *str);
/* ENV CATCHING */
// t_env* makenode(char *data);
// t_env *catch_env(char **env, t_env* head);
// void print_env(t_env *head);
// t_env	*ft_lstnew(char *content);
// void	ft_lstadd_back(t_env **lst, t_env *new);
void print_environ(void);
// void catch_environ(t_env **lenv, char **env);
// t_env	*ft_lstlast(t_env *lst);
void print_env(t_var_t *head, int bool);
void free_env(t_var_t *head);
void initialize_environment(t_var_t **head, char **env);
int add_env_var(t_var_t **head, char *key, char *value);
int ft_strcmp(const char *s1, const char *s2);
int ft_charfind(const char *str, char c);
char* env_nav(t_var_t **head,char * key);
char *better_prompt(void);
static int	skip_sep(char *s);
static int	ft_word_len(char *s);
static int	ft_count(char *s);
char	**ft_strsplit(char *s);
void token_list(t_tlist **head,char *tok, int type);
void add_token_list(t_tlist **head, char **tab);
int typefinder (char *line);
void print_tokens(t_tlist *head);
void add_to_env(t_var_t **head, char *env);
void modify_env(t_tlist *token);
char * expanded(char* str);
void expander_init(t_tlist *head, t_var_t *env);
int find_in_list(t_var_t *head, char* search);
void qidentify(t_tlist *token);
#endif