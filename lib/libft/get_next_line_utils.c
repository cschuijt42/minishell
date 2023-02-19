/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 22:34:36 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/31 22:22:50 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Calls read() on fd, putting the result in *buffer and null terminating it.
// Old data may remain beyond the null terminator if return from read() is
// shorter than the buffer size. If read reaches EOF or errors, buffer_pos
// is moved to the end of the buffer to avoid illegal reads, else it is
// set to the start of the buffer.
//
// Freeing, if necessary, is handled in this function. If the return value is
// 0, only the buffer is freed, since we are done reading the file but the line
// still needs returning. If it's <0, line is also freed to be able to return
// NULL on error.
//
// Returns amount of bytes read, the same value as read() returns.
int	get_next_buffer(int fd, char **buffer, size_t *buffer_pos, char **line)
{
	int	read_bytes;

	read_bytes = read(fd, *buffer, BUFFER_SIZE);
	if (read_bytes <= 0)
		*buffer_pos = BUFFER_SIZE;
	else
	{
		(*buffer)[read_bytes] = '\0';
		*buffer_pos = 0;
	}
	if (read_bytes < 0)
	{
		free(*line);
		*line = NULL;
	}
	if (read_bytes <= 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (read_bytes);
}

// Returns the amount of characters from buffer to the first newline or to
// the null terminator. Can be used as a ft_strlen in a pinch :)
// If a null pointer is given, return value will always be 0.
int	length_to_nl(char *buffer)
{
	int	i;

	if (!buffer)
		return (0);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	return (i);
}

// Adds n bytes of string "to_add" to the back of string "old", allocating the
// resulting string. If old is NULL, length_to_nl(*old) will also be zero,
// meaning the function will not copy anything from old and create just a new
// string with n bytes from to_add and a null terminator. If old
// already exists, a new null-terminated string is allocated containing both
// strings, concatenated, the old pointer is overridden and the original
// old is freed. This way, calling this method should always leave you with at
// most one string in memory, and all building blocks freed.
//
// Return value is the amount of bytes added to the original old string,
// excluding the null byte.
//
// It is assumed that to_add is part of the buffer, and therefore will be freed
// separately when needed. In case of failure, only old and new are freed, and
// the old pointer is set to NULL to indicate failure.
int	add_to_str(char **old, char *to_add, size_t n)
{
	char	*new;
	int		old_length;

	old_length = length_to_nl(*old);
	new = malloc(n + old_length + 1);
	if (!new)
	{
		free(*old);
		*old = NULL;
		return (0);
	}	
	ft_strcpy(new, *old, old_length);
	ft_strcpy(new + old_length, to_add, n);
	free(*old);
	*old = new;
	return ((int) n);
}

// Copies n bytes from the source string to the destination string,
// null-terminating the result. The null terminator is added to n, meaning n + 1
// bytes will be written in total. Dst should point to where the copying should
// begin, it does not walk to the end of the string first to allow working on
// fresh allocations.
// Quick and dirty solution, absolutely unsafe when it comes to overflows.
// Ensure enough space is available!
void	ft_strcpy(char *dst, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

// Returns 1 if the string ends in a \n character, else returns 0.
// Also returns 0 if str is a NULL pointer.
int	ends_in_newline(char *str)
{
	if (!str)
		return (0);
	while (*str)
		str++;
	str--;
	return (*str == '\n');
}
