/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:55:19 by nbouhali          #+#    #+#             */
/*   Updated: 2023/02/11 23:32:04 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlengnl(char *s);
ssize_t	pos(char *s, char c);
char	*ft_strjoingnl(char *s1, char *s2);
char	*ft_substrgnl(char *s, unsigned int start, size_t len);
char	*n9esmnjoin(char *str);
void	ft_bzerognl(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*reader(int fd, char *join, int *readd);
#endif