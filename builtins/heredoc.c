#include "builtins.h"

t_heredoc *new_here(int fd)
{
	t_heredoc *new;

	new = malloc(sizeof(t_heredoc));
	new->fd = fd;
	new->next = NULL;
	return (new);
}

void add_here(t_heredoc **node, t_heredoc *new)
{
	t_heredoc *head;

	if (!*node)
	{
		*node = new;
		return;
	}
	head = *node;
	while (head->next)
		head = head->next;
	head->next = new;
}

void    heredoc(t_shell *g_struct, char *eof)
{
    int pipes[2];
    char *line;

    pipe(pipes);
    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(0);
        line = ft_strtrim(line, "\n");
        if (ft_strcmp(line, eof) == 0)
		{
			free(line);
            break;
		}
        ft_putstr_fd(line, pipes[1]);
		ft_putstr_fd("\n", pipes[1]);
		free(line);
    }
    close(pipes[1]);
    add_here(&g_struct->heredoc_list, new_here(pipes[0]));
}