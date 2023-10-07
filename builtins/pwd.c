#include "builtins.h"

void	pwd_command(t_shell *g_shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		error_set(g_shell, PERMISSION_DENIED_FILE, 1);
		return ;
	}
	g_shell->error_name = SUCCESS;
	exit_status_error(g_shell);
	return ;
}
