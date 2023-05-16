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

void	setup_input_redirect(t_redirect *redirect)
{
	int	fd;

	if (access(redirect->target, F_OK) == -1)
		exit(print_error_message_perror("infile doesn't exist", 1));
	fd = open(redirect->target, O_RDONLY);
	if (fd == -1)
		exit(print_error_message_perror("can't open infile", 1));
	dup2(fd, 0);
	close(fd);
}

void	setup_output_redirect(t_redirect *redirect)
{
	int		fd;

	if (redirect->type == redirect_output_append)
		fd = open(redirect->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(redirect->target, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		exit(print_error_message_perror("can't open outfile", 1));
	dup2(fd, 1);
	close(fd);
}

void	setup_heredoc_redirect(t_command *command)
{
	dup2(command->heredoc_pipe[0], 0);
}
