/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:10:58 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 05:07:16 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_var_t	*find_value(char *key, t_var_t *head, char *value)
{
	t_var_t	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

char	*find_key(char *key, t_var_t *head)
{
	t_var_t	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

void	change_pwd(t_var_t *head, t_shell *g_shell)
{
	t_var_t	*old_pwd;
	t_var_t	*current_pwd;
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	find_value("OLDPWD", head, find_key("PWD", head));
	find_value("PWD", head, pwd);
}

void	cd_command(char *directory, char **env, t_shell *g_shell)
{
	if (!directory)
		chdir(extract_from_in_list(g_shell, g_shell->envlist, "PATH"));
	else if (chdir(directory) != 0)
	{
		error_set(g_shell, PERMISSION_DENIED_FILE, 1);
		return ;
	}
	change_pwd(g_shell->envlist, g_shell);
	error_set(g_shell, SUCCESS, 0);
	return ;
}
