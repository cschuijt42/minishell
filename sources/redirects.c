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

int	setup_input_redirect(t_redirect *redirect)
{
	int	fd;

	if (access(redirect->target, F_OK) == -1)
		return (error_cant_access_infile);
	fd = open(redirect->target, O_RDONLY);
	if (fd == -1)
		return (error_cant_open_infile);
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		return (error_cant_dup_fd);
	}
	close(fd);
	return (error_continue);
}

int	setup_output_redirect(t_redirect *redirect)
{
	int		fd;

	if (redirect->type == redirect_output_append)
		fd = open(redirect->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(redirect->target, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (error_cant_access_outfile);
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (error_cant_dup_fd);
	}
	close(fd);
	return (error_continue);
}

int	setup_heredoc_redirect(t_command *command)
{
	if (dup2(command->heredoc_pipe[0], 0) == -1)
		return (error_cant_dup_fd);
	return (error_continue);
}
