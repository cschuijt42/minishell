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

void	setup_input_redirect(t_command *command, t_redirect *redirect)
{
	(void) command;
	if (access(redirect->target, F_OK | R_OK))
	// does file exist if not error

	(void) redirect;
}

void	setup_output_redirect(t_command *command, t_redirect *redirect, \
								int append_mode)
{
	int		fd;
	mode_t	mode;

	(void) command;
	(void) redirect;
	mode =
	if (append_mode)
		fd = open(O_CREATE | O_APPEND);
	else
		fd = open(O_CREATE | )
	(void) append_mode;
	// if append mode and file exists point fd to end of file
	//
}

void	setup_heredoc_redirect(t_command *command, t_redirect *redirect)
{
	(void) command;
	// dup2(command->pipe_out)
	(void) redirect;
}
