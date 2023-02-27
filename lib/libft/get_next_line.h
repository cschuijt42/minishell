/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 22:20:14 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/30 22:54:48 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 1024

# endif

char	*get_next_line(int fd);

int		get_next_buffer(int fd, char **buffer, size_t *buffer_pos, char **line);
int		add_to_str(char **old, char *to_add, size_t n);
void	ft_strcpy(char *dst, char *src, size_t n);
int		length_to_nl(char *buffer);
int		ends_in_newline(char *str);

#endif
