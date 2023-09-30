#include "builtins.h"


void pwd_command(t_shell *g_shell)
{
        char cwd[1024];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("%s\n",cwd);
        else
        {
            g_shell->error_name = PERMISSION_DENIED_FILE;
            exit_status_error(g_shell);
            print_error_message(g_shell);
            return;
        }
        return;
}