#include "../builtins.h"

// make e num with shortcuts to errors
void print_error_message(t_shell *g_shell)
{
    if (g_shell->error_name == SYNTAX_ERROR)
        ft_putstr_fd("minishell: Syntax Error\n", 2);
    else if (g_shell->error_name == COMMAND_NOT_FOUND)
        ft_putstr_fd("minishell: Command not found\n", 2);
    else if (g_shell->error_name == PROGRAM_NOT_FOUND)
        ft_putstr_fd("minishell: Program not found\n", 2);
    else if (g_shell->error_name == PERMISSION_DENIED_PROGRAM)
        ft_putstr_fd("minishell: Permission denied for program execution\n", 2);
    else if (g_shell->error_name == FILE_NOT_FOUND)
        ft_putstr_fd("minishell: File not found\n", 2);
    else if (g_shell->error_name == PERMISSION_DENIED_FILE)
        ft_putstr_fd("minishell: Permission denied for file operation\n", 2);
    else if (g_shell->error_name == TOO_MANY_ARGUMENTS)
        ft_putstr_fd("minishell: Too many arguments\n", 2);
    else if (g_shell->error_name == NUMERIC_ARG_REQUIRED)
        ft_putstr_fd("minishell: Numeric argument required\n", 2);
    else if (g_shell->error_name == HOME_NOT_SET)
        ft_putstr_fd("minishell: HOME environment variable not set\n", 2);
    else if (g_shell->error_name == INVALID_UNSET_IDENTIFIER)
        ft_putstr_fd("minishell: Invalid identifier for unset command\n", 2);
    else if (g_shell->error_name == INVALID_EXPORT_IDENTIFIER)
        ft_putstr_fd("minishell: Invalid identifier for export command\n", 2);
    else if (g_shell->error_name == SUCCESS)
        ft_putstr_fd("minishell: No error, command completed successfully\n", 2);
}

void exit_status_error(t_shell *g_shell)
{
    if (g_shell->error_name == SYNTAX_ERROR)
        g_shell->exit_status = 258;
    else if (g_shell->error_name == COMMAND_NOT_FOUND || g_shell->error_name == PROGRAM_NOT_FOUND)
        g_shell->exit_status = 127;
    else if (g_shell->error_name == PERMISSION_DENIED_PROGRAM || g_shell->error_name == PERMISSION_DENIED_FILE)
        g_shell->exit_status = 126;
    else if (g_shell->error_name == FILE_NOT_FOUND ||
             g_shell->error_name == TOO_MANY_ARGUMENTS ||
             g_shell->error_name == NUMERIC_ARG_REQUIRED ||
             g_shell->error_name == HOME_NOT_SET ||
             g_shell->error_name == INVALID_UNSET_IDENTIFIER ||
             g_shell->error_name == INVALID_EXPORT_IDENTIFIER)
        g_shell->exit_status = 1;
    else if (g_shell->error_name == SUCCESS)
        g_shell->exit_status = 0;
}
void error_set(t_shell *g_shell, t_shell_error error_name, int print)
{
        g_shell->error_name = error_name;
        exit_status_error(g_shell);
        if (print == 1)
            print_error_message(g_shell);
}