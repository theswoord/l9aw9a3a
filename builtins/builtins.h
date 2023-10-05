#ifndef BUILTINS_H
#define BUILTINS_H


#define OUT 2
#define APPEAND 9
#define IN 3
#define HEREDOC 4


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../minishell.h"
// typedef struct env_vars
// {
// 	char *key;
// 	char *value;
// 	struct env_vars *next;
// } t_var_t;






// extern t_var_t *g_struct;

int ft_charfind(const char *str, char c);
int ft_strcmp(const char *s1, const char *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strchr(const char *s, int c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strdup(const char *s1);
void *ft_memcpy(void *dst, const void *src, size_t n);
char *ft_strjoin(char const *s1, char const *s2);
void ft_putstr_fd(char *s, int fd);
size_t ft_strlen(const char *str);
// void print_env(t_var_t *head, int bool);
// void	initialize_environment(t_var_t **head, char **env);
// void add_env_var(t_var_t **head, char *key, char *value);
void execute_commands(char *command, char **args, char **env, t_shell *g_shell);
// void execute_pipelines(array_of_commands *command_list, char **env);
// void execute_pipelines(t_node **command_node, char **env);
void execute_pipelines(t_node **command_node, t_shell *g_struct);
// void cd_command(int ac, char **av);
void echo_command(int ac, char **av, t_shell *g_struct);
// void ft_env(t_shell *g_struct, int ac, char **av);
char *find_executable_command(char *command, char *path);
void ft_exit_error(int case_num, char *command);
int valid_arg(char *arg);
// void ft_exit(char **args);
// void add_to_environ(char *argument, t_var_t **env);
// void export(t_shell *g_struct, int ac, char **av, char **env);
void pwd_command(t_shell *g_shell);
int find_delimeter(char *string, char *delimeter);
// void redirect_into_file(ParsedCommand *data);
// void redirect_heredoc(ParsedCommand *data);
// void redirect_input(ParsedCommand *data);
// void ft_redirect(ParsedCommand *data);
// void unset_var_env(t_var_t **head, char *key);
void ft_unset(int ac, char **av, t_shell *g_struct);
// void cd_command(int ac, char **av, char **env, t_shell *g_struct);
void output_out(int fd);
void output_in(int fd);
void file_out(char *file);
void file_append(char *file);
void file_in(char *file);
void redirections(t_redi_node *redirect_node, t_shell *g_struct);
t_redi_node *new_redi(char *file, int type);
t_node	*new_node(char **arr, t_redi_node *redirect);
void add_redi(t_redi_node **node, t_redi_node *new);
void	add_node(t_node **node, t_node *new);
// void execute_commands_pipes(char *command, char **args, char **env);
void execute_commands_pipes(char *command, char **args, char **env, t_shell *g_shell);
void ft_exit(char **args, t_shell *g_struct);
int	allspaces(char *str);
#endif