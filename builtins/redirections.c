/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:11:37 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 04:11:38 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	output_out(int fd)
{
	dup2(fd, 1);
	close(fd);
}

void	output_in(int fd)
{
	dup2(fd, 0);
	close(fd);
}

void	file_out(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	output_out(fd);
}

void	file_append(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	output_out(fd);
}

void	file_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	output_in(fd);
}
