/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 19:19:31 by mde-cloe      #+#    #+#                 */
/*   Updated: 2022/08/02 21:08:53 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buff[OPEN_MAX + 1];

	if (read(fd, 0, 0) == -1 || BUFFER_SIZE < 1 || !set_buff(buff, fd))
		return (NULL);
	line = stralloc(1);
	if (!line)
		return (NULL);
	if (*buff[fd])
	{
		line = buff_to_line(buff[fd], line);
		if (!line)
			return (NULL);
	}
	line = read_till_nl(buff[fd], line, fd);
	if (!line)
		return (NULL);
	buff_update(buff[fd]);
	if (!*line)
	{
		free(buff[fd]);
		buff[fd] = NULL;
		return (free(line), NULL);
	}
	return (line);
}

char	*read_till_nl(char *buff, char *line, int fd)
{
	int	read_ret;

	read_ret = 1;
	while (!delimlen(line, '\n') && read_ret > 0)
	{
		read_ret = read(fd, buff, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
		buff[read_ret] = '\0';
		line = buff_to_line(buff, line);
		if (!line)
			return (NULL);
	}
	return (line);
}

int	set_buff(char **buff, int fd)
{
	if (!buff[fd])
		buff[fd] = stralloc(BUFFER_SIZE + 1);
	if (!buff[fd])
		return (0);
	return (1);
}
