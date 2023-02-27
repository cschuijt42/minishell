/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 22:22:21 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/31 22:22:40 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// The big boy function.
//
// START
// At first, a buffer pointer and iterator pos are created. Pos initially gets
// set to the end of the buffer to immediately prompt a buffer refresh in the
// following loop. Malloc failure for the buffer is protected. Also, a line
// pointer is initiated to collect buffer parts until we find a newline or EOF.
//
// LOOP
// The loop continues until what has been put into line ends in \n. If EOF is
// encountered or an error occurs, the loop gets broken and line gets returned
// as it is up to that point, which is either the last line (in case of EOF or
// rolling read failure) or NULL (in case of a malloc or initial read failure).
//
// The loop flow is as follows:
//   - Check if we've reached the end of the buffer, and if so, run
//     get_next_buffer to get a new one and reset the position.
//   - Discover how much we need to grab from buffer before encountering a
//     newline or the end of the buffer, then add that to the end of line.
//   - Check if line now ends in a newline. If so, we're done. If not, we
//     start again from the top.
// This continues until we've got the next line together, which is the
// return value. When there is nothing more to read or an error occurs,
// the return value is NULL.
char	*get_next_line(int fd)
{
	static char		*buffer = NULL;
	static size_t	pos = BUFFER_SIZE;
	char			*line;

	if (!buffer)
		buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = NULL;
	while (!ends_in_newline(line))
	{
		if (pos >= BUFFER_SIZE || !buffer[pos] || !buffer[pos - 1])
			if (get_next_buffer(fd, &buffer, &pos, &line) <= 0)
				break ;
		pos += add_to_str(&line, &buffer[pos], length_to_nl(&buffer[pos]) + 1);
		if (!line)
		{
			free(buffer);
			break ;
		}
	}
	return (line);
}
