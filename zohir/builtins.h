#ifndef BULITINS_H
#define BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
typedef struct env_vars
{
	char *key;
	char *value;
	struct env_vars *next;
} t_var_t;

typedef struct
{
    char *command;
    char **arguments;
    char *output_file;
    char *redirection_operator;
    int O_REDI;
} ParsedCommand;


extern t_var_t *g_struct;

int ft_charfind(const char *str, char c);
int ft_strcmp(const char *s1, const char *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strchr(const char *s, int c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strdup(const char *s1);
void *ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
size_t ft_strlen(const char *str);
void print_env(t_var_t *head, int bool);
void	initialize_environment(t_var_t **head, char **env);
void add_env_var(t_var_t **head, char *key, char *value);

#endif