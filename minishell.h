/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:50:46 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 08:03:23 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./ft_malloc/ft_malloc.h"
# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>

typedef enum s_types
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
}						t_tokenum;

typedef enum s_shell_error
{
	SYNTAX_ERROR,
	COMMAND_NOT_FOUND,
	PROGRAM_NOT_FOUND,
	PERMISSION_DENIED_PROGRAM,
	FILE_NOT_FOUND,
	PERMISSION_DENIED_FILE,
	TOO_MANY_ARGUMENTS,
	NUMERIC_ARG_REQUIRED,
	HOME_NOT_SET,
	INVALID_UNSET_IDENTIFIER,
	INVALID_EXPORT_IDENTIFIER,
	SUCCESS
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

typedef struct s_index
{
	int					i;
	int					j;
	int					k;
	char				*out;
	char				*result;

}						t_lesindex;

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
	t_node				*pipes_list;
	t_heredoc			*heredoc_list;
	t_tokenum			tokenum;
	char				**env;
	int					count;
	int					exit_status;
	char				*exit_arr;
	t_shell_error		error_name;
	t_redi_node			*redi_list;
}						t_shell;

void					tokenisation(char *str, t_shell *mstruct, int ac,
							char **av);
void					element_init(t_counter *elements, char *str);
int						syntax_check(t_counter *elements, char *str);
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
void					str_replacement(char *str);
char					*ft_strtok(char *str);
void					free_tableau(char **tableau, int lines);
char					*ft_substrmini(char *s, unsigned int start, size_t len);
char					*toktok(char *str);
void					print_env(t_var_t *head, int boole);
void					free_env(t_var_t *head);
void					initialize_environment(t_shell *mstruct, t_var_t **head,
							char **env);
int						add_env_var(t_var_t **head, char *key, char *value);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_charfind(const char *str, char c);
char					*env_nav(t_var_t **head, char *key);
char					**ft_u_split(char *s);
void					token_list(t_tlist **head, char *tok, int type,
							int queue);
void					add_token_list(t_tlist **head, char **tab);
int						typefinder(char *line);
void					modify_env(t_shell *mstruct, t_tlist *token);
char					*expanded(t_shell *mstruct, char *str);
void					expander_init(t_shell *mstruct, t_tlist *head);
void					qidentify(t_shell *mstruct, t_tlist *token);
void					add_to_environ(char *argument, t_var_t **env);
int						list_size(t_tlist *head);
char					**from_list_to_arr(t_tlist *head);
t_var_t					*find_value(char *key, t_var_t *head, char *value);
char					*find_key(char *key, t_var_t *head);
void					change_pwd(t_var_t *head);
void					cd_command(char *directory, t_shell *g_shell);
char					*expanded_q(t_shell *mstruct, char *str);
char					*ft_strchrtill(const char *s, int c, int len);
char					*strdelch(char *str, char ch);
void					free_tokens(t_tlist *head);
void					free_env(t_var_t *head);
bool					quotes_errors(char *str);
bool					list_check(t_tlist *head);
char					*delete_pos(char *str, int pos);
char					*recombinator(char *first, char *later, char *rest);
int						command_id(t_tlist *head);
void					pipes_divider(t_shell *mstruct);
char					*quotes_remover(char *str);
t_tlist					*pipes_copy(t_tlist *current);
void					free_tableauv2(char **tableau);
void					execute_pipelines(t_node **command_node,
							t_shell *mstruct);
void					free_pipes(t_node *head);
void					free_pipes_node(t_node **command_node);
t_node					*new_command_node(t_node **list, char **args);
t_node					*new_node(char **arr, t_redi_node *redirect);
void					add_node(t_node **node, t_node *new);
void					execute_commands(char *command, char **args,
							t_shell *g_shell);
void					special_free(t_shell *mstruct);
void					print_pointers(t_tlist *head);
void					files_finder(t_tlist *head);
void					add_redi(t_redi_node **node, t_redi_node *new);
t_redi_node				*new_redi(char *file, int type);
void					add_node(t_node **node, t_node *new);
void					redi_set(t_shell *mstruct);
char					*expander_qv2(t_shell *mstruct, char *str);
char					*env_expander(t_var_t *head, char *key);
void					print_pointers2(t_redi_node *head);
// void cd_command(int ac, char *directory, char **env, t_shell *mstruct);
void					execute_commands_pipes(char *command, char **args,
							char **env, t_shell *g_shell);
void					export(t_shell *mstruct, int ac, char **av, char **env);
void					ft_unset(int ac, char **av, t_shell *mstruct);
void					exit_status_expand(t_shell *g_shell, int free_memory);
void					ft_exit(char **args, t_shell *mstruct);
void					exit_status_error(t_shell *g_shell);
void					print_error_message(t_shell *g_shell);
void					pwd_command(t_shell *g_shell);
void					echo_command(int ac, char **av, t_shell *mstruct);
char					*extract_from_in_list(t_shell *mstruct, t_var_t *tlist,
							char *key);
t_heredoc				*new_here(int fd);
void					add_here(t_heredoc **node, t_heredoc *new);
void					heredoc(t_shell *mstruct, char *eof);
// void echo_command(int ac, char **av);
char					*extract_from_in_list(t_shell *mstruct, t_var_t *tlist,
							char *key);
void					ft_env(t_shell *mstruct, int ac, char **av);
void					echo_command(int size, char **args, t_shell *mstruct);
char					*ft_strjoinmini(char *s1, char *s2);
char					*ft_realloc(char *str, int size);
char					*add_exit_to_env(t_shell *mstruct); // here
void					update_exit(t_shell *mstruct);
int						allspaces(char *str);
void					builtins(t_shell *mstruct, char **env,
							char **single_comm);
int						element_counter(t_shell *mstruct, t_tlist *head,
							int what);
int						nodes_count(t_tlist **current);
void					pipes_list(t_shell *mstruct, int count, int i);
void					free_tokens3(t_tlist *head);
void					general_execution(t_shell *mstruct, char **args,
							int fork);
void					error_set(t_shell *g_shell, t_shell_error error_name,
							int print);
#endif