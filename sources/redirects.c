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
	(void) redirect;
}

void	setup_output_redirect(t_command *command, t_redirect *redirect, \
								int append_mode)
{
	(void) command;
	(void) redirect;
	(void) append_mode;
}

void	setup_heredoc_redirect(t_command *command, t_redirect *redirect)
{
	(void) command;
	(void) redirect;
}
