#include "builtins.h"

void output_out(int fd)
{
    dup2(fd, 1);
    close(fd);
}

void output_in(int fd)
{
    dup2(fd, 0);
    close(fd);
}

void file_out(char *file)
{
    int fd;

    fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    output_out(fd);
}

void file_append(char *file)
{
    int fd;

    fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    output_out(fd);
}

void file_in(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    output_in(fd);
}

void redirections(t_redi_node *redirect_node)
{
    t_redi_node *current;

    current = redirect_node;
    while (current)
    {
        if (current->type == OUT)
            file_out(current->file);
        else if (current->type == APPEND)
            file_append(current->file);
        else if (current->type == IN)
            file_in(current->file);
        else
            return;
        current = current->next;
    }
}

t_redi_node *new_redi(char *file, int type)
{
    t_redi_node *new;

    new = malloc(sizeof(t_redi_node));
    new->file = file;
    new->type = type;
    new->next = NULL;
    return (new);
}

void add_redi(t_redi_node **node, t_redi_node *new)
{
    t_redi_node *head;

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

// int main()
// {
//     t_redi_node *redirect = NULL;
//     char file[] = "text";
//     char type[] = "out";
//     head_tiz(&redirect, new_tiz(file, type));

//     char file1[] = "kkk";
//     char type1[] = "in";
//     head_tiz(&redirect, new_tiz(file1, type1));

//     char file2[] = "tizk";
//     char type2[] = "append";
//     head_tiz(&redirect, new_tiz(file2, type2));

//     redirections(redirect);
// }