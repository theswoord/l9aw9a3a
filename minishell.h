#ifndef MINISHELL_H
# define MINISHELL_H
# include "./ft_malloc/ft_malloc.h"
# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
// #include "./builtins/builtins.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
// #define PIPE = 5
// int g_grlobal;
// enum tokens
// {

// };

typedef enum
{
	ANTI0,
	PIPE,
	REDIW,
	REDIR,
	DOC,
	WORD,
	OPT,
	EXPAND,
	VAR,
	APPEND,
	QUOTES,
	SQUOTE,
	DQUOTE,
	ISFILE,
}						e_tokenum;

typedef enum s_shell_error
{
	SYNTAX_ERROR,              // Syntax error in the command
	COMMAND_NOT_FOUND,         // Command not found in the system's PATH
	PROGRAM_NOT_FOUND,         // Program or binary file not found
	PERMISSION_DENIED_PROGRAM, // Permission denied for executing a program
	FILE_NOT_FOUND,            // File not found
	PERMISSION_DENIED_FILE,    // Permission denied for a file operation
	TOO_MANY_ARGUMENTS,        // Too many arguments provided
	NUMERIC_ARG_REQUIRED,      // Numeric argument required (e.g.,
	HOME_NOT_SET,              // HOME environment variable not set
	INVALID_UNSET_IDENTIFIER,  // Invalid identifier for the "unset" command
	INVALID_EXPORT_IDENTIFIER, // Invalid identifier for the "export" command
	SUCCESS                    // Successful execution (no error)

}						t_shell_error;

typedef struct s_heredoc
{
	int					fd;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_redi_node
{
	char				*file;
	int					type;
	struct s_redi_node	*next;
}						t_redi_node;

typedef struct s_node
{
	char				**args;
	t_redi_node			*redirect;
	struct s_node		*next;
	int					total;
}						t_node;

typedef struct env_vars
{
	char				*key;
	char				*value;
	struct env_vars		*next;
}						t_var_t;

typedef struct s_tlist
{
	int					value;
	char				*str;
	int					queue;
	bool				is_file;

	struct s_tlist		*next;
	struct s_tlist		*prev;

}						t_tlist;

typedef struct s_tree
{
	char				*data;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;

typedef struct s_prompt
{
	char				*command;
	char				*cmd;
	char				**flags;
	char				**tempdevider;
	int					twodlen;

}						t_prompt;

typedef struct s_counter
{
	int					quotes;
	int					d_quotes;
	int					pipes;
	int					r_left;
	int					r_right;

}						t_counter;

typedef struct s_shell
{
	t_tlist				*tlist;
	t_var_t				*envlist;
	char				**env;
	t_node				*pipes_list;
	t_heredoc			*heredoc_list;
	e_tokenum			tokenum;
	int count; // hada test o safi
	// int exit_status; //static int
	int					exit_status;
	t_shell_error		error_name;
	t_redi_node			*redi_list;
}						t_shell;

// extern t_shell	g_struct;
// typedef struct s_tre
// {
// 	char *token;
// 	char *type;
// 	struct s_tre	*left;
// 	struct s_tre	*right;
// 	struct s_tre	*parent;

// }t_tre;

/*	----	----lexer----	-----	*/
void					tokenisation(char *str, t_shell *g_struct, char **env);
void					element_init(t_counter *elements, char *str);
int						syntax_check(t_counter *elements, char *str);
/*	----	----utils----	-----	*/
int						e_search(char *str, char c);
char					*quotefixer(char *str, char quote);
int						closed_quotes(char *str);
int						closed_double_quotes(char *str);
char					*code_3_quotes(char *str);
char					*special_trim(char *str, char c);
char					*simple_trim(char *str, char c);
void					the_divider(t_prompt *helper, t_counter *elements,
							char *str);
int						twodlen(char **tableau);
void					quoter(t_prompt *helper);
void					str_replacement(char *str);
// int quotation(char *str,int c);
void					linkwithex(char **tableau);
char					*ft_strtok(char *str);
// void strr_replacement(char *str);
/*	----	----temp----	-----	*/
int						isQuotesClosed(const char *str);
/*	----	----free----	-----	*/
void					free_tableau(char **tableau, int lines);
/*	----	----print----	-----	*/
void					printTree(struct s_tree *root);
void					printInOrderIndented(struct s_tree *node, int depth);
void					printBinaryTree(struct s_tree *root, int level,
							char direction);
void					printSpaces(int count);
/*	----	----tree----	-----	*/
void					insertNode(struct s_tree **root, char *data);
void					freeTree(struct s_tree *node);
/*  ----    ----list----    -----   */
// t_list *l_addnode(char* data);
// int list_size(t_list *head);
// void l_addback(t_list*list,char *data);
// void l_print(t_list *list);
// t_list *create_node(char* s);
// void add_list(t_list **head,char *s);
char					*ft_substrmini(char *s, unsigned int start, size_t len);
char					*toktok(char *str);
/* ENV CATCHING */
// t_env* makenode(char *data);
// t_env *catch_env(char **env, t_env* head);
// void print_env(t_env *head);
// t_env	*ft_lstnew(char *content);
// void	ft_lstadd_back(t_env **lst, t_env *new);
void					print_environ(void);
// void catch_environ(t_env **lenv, char **env);
// t_env	*ft_lstlast(t_env *lst);
void					print_env(t_var_t *head, int boole);
void					free_env(t_var_t *head);
void					initialize_environment(t_shell *g_struct,
							t_var_t **head, char **env);
int						add_env_var(t_var_t **head, char *key, char *value);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_charfind(const char *str, char c);
char					*env_nav(t_var_t **head, char *key);
char					*better_prompt(void);
static int				skip_sep(char *s);
static int				ft_word_len(char *s);
static int				ft_count(char *s);
char					**ft_strsplit(char *s);
void					token_list(t_tlist **head, char *tok, int type,
							int queue);
void					add_token_list(t_tlist **head, char **tab);
int						typefinder(char *line);
void					print_tokens(t_tlist *head);
void					add_to_env(t_var_t **head, char *env);
void					modify_env(t_shell *g_struct, t_tlist *token);
char					*expanded(t_shell *g_struct, char *str);
void					expander_init(t_shell *g_struct, t_tlist *head,
							t_var_t *env);
int						find_in_list(t_var_t *head, char *search);
void					qidentify(t_shell *g_struct, t_tlist *token);
void					add_to_environ(char *argument, t_var_t **env);
int						list_size(t_tlist *head);
// void execute_pipelines(array_of_commands *command_list, char **env);
char					**from_list_to_arr(t_tlist *head);
t_var_t					*find_value(char *key, t_var_t *head, char *value);
char					*find_key(char *key, t_var_t *head);
// void change_pwd(t_var_t *head);
void					change_pwd(t_var_t *head, t_shell *g_shell);
void					cd_command(char *directory, char **env,
							t_shell *g_shell);
char					*expanded_q(t_shell *g_struct, char *str);
char					*ft_strchrtill(const char *s, int c, int len);
char					*strdelch(char *str, char ch);
void					free_tokens(t_tlist *head);
void					free_env(t_var_t *head);
bool					quotes_errors(char *str);
bool					list_check(t_tlist *head);
char					*delete_pos(char *str, int pos);
char					*recombinator(char *first, char *later, char *rest);
int						command_id(t_tlist *head);
void					pipes_divider(t_shell *g_struct);
char					*quotes_moncef(char *str);
t_tlist					*pipes_copy(t_tlist *head, t_tlist *current);
void					free_tableauv2(char **tableau);
// void execute_pipelines(t_node **command_node, char **env);
void					execute_pipelines(t_node **command_node,
							t_shell *g_struct);
void					free_pipes(t_node *head);
void					free_pipes_node(t_node **command_node);
t_node					*new_command_node(t_node **list, char **args);
t_node					*new_node(char **arr, t_redi_node *redirect);
void					add_node(t_node **node, t_node *new);
void					execute_commands(char *command, char **args, char **env,
							t_shell *g_shell);
void					special_free(t_shell *g_struct);
void					special_free_recursive(t_shell *g_struct,
							t_tlist *current);
void					special_freex(t_shell *g_struct);
void					print_pointers(t_tlist *head);
void					versatile_divider(t_shell *g_struct);
int						versatile_nodes_count(t_tlist **current);
void					versatile_pipes_list(t_shell *g_struct, int count,
							bool detected);
int						versatile_counter(t_tlist *head);
void					files_finder(t_tlist *head);
void					add_redi(t_redi_node **node, t_redi_node *new);
t_redi_node				*new_redi(char *file, int type);
void					add_node(t_node **node, t_node *new);
void					redi_set(t_shell *g_struct);
char					*expander_qv2(t_shell *g_struct, char *str);
char					*env_expander(t_shell *g_struct, t_var_t *head,
							char *key);
void					print_pointers2(t_redi_node *head);
// void cd_command(int ac, char *directory, char **env, t_shell *g_struct);
void					execute_commands_pipes(char *command, char **args,
							char **env, t_shell *g_shell);
void					export(t_shell *g_struct, int ac, char **av,
							char **env);
void					ft_unset(int ac, char **av, t_shell *g_struct);
void					exit_status_expand(t_shell *g_shell, int free_memory);
void					ft_exit(char **args, t_shell *g_struct);
void					exit_status_error(t_shell *g_shell);
void					print_error_message(t_shell *g_shell);
void					pwd_command(t_shell *g_shell);
void					echo_command(int ac, char **av, t_shell *g_struct);
char					*extract_from_in_list(t_shell *g_struct, t_var_t *tlist,
							char *key);
t_heredoc				*new_here(int fd);
void					add_here(t_heredoc **node, t_heredoc *new);
void					heredoc(t_shell *g_struct, char *eof);
void					general_execution(t_shell *g_struct, char **args,
							int fork);
void					ft_env(t_shell *g_struct, int ac, char **av);
void					error_set(t_shell *g_shell, t_shell_error error_name,
							int print);
#endif