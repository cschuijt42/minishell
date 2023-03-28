/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 15:03:28 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/03/27 15:03:28 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <fcntl.h>

void	setup_input_redirect(t_command *command, t_redirect *redirect)
{
	int	fd;

	(void) command;
	if (access(redirect->target, F_OK) == -1)
		error_exit("infile doesn't exist", errno);
	fd = open(redirect->target, O_RDONLY);
	if (fd == -1)
		error_exit("can't open infile", errno);
	dup2(fd, 0);
	close(fd);
}


// do we want protection on our dups and closes?
void	setup_output_redirect(t_command *command, t_redirect *redirect, \
								int append_mode)
{
	int		fd;

	(void) command;
	if (append_mode)
		fd = open(redirect->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(redirect->target, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		error_exit("cant open outfile", errno);
	dup2(fd, 1);
	close(fd);
}

void	setup_heredoc_redirect(t_command *command, t_redirect *redirect)
{
	dup2(command->heredoc_pipe[0], 0);
}
