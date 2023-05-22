/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_redirects.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 14:53:18 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/22 14:53:18 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

int	setup_command_redirects_builtin(t_command *command)
{
	t_redirect	*redirect;
	int			return_value;

	redirect = command->redirects;
	return_value = error_continue;
	while (redirect)
	{
		if (redirect->type == redirect_input)
			return_value = setup_input_redirect(redirect);
		else if (redirect->type == redirect_output || \
					redirect->type == redirect_output_append)
			return_value = setup_output_redirect(redirect);
		else
			return_value = setup_heredoc_redirect(command);
		redirect = redirect->next;
		if (return_value == error_cant_access_infile)
			return (print_error_message_perror("can't access infile", false));
		else if (return_value == error_cant_open_infile)
			return (print_error_message_perror("can't open infile", false));
		else if (return_value == error_cant_access_outfile)
			return (print_error_message_perror("can't access outfile", false));
		else if (return_value == error_cant_dup_fd)
			return (print_error_message_perror(ERROR_MESSAGE_FD, false));
	}
	return (true);
}

int	backup_stdin_out(int *temp_inout)
{
	temp_inout[0] = dup(0);
	if (temp_inout[0] == -1)
	{
		return (print_error_message_perror(ERROR_MESSAGE_FD, false));
	}
	temp_inout[1] = dup(1);
	if (temp_inout[1] == -1)
	{
		close(temp_inout[0]);
		return (print_error_message_perror(ERROR_MESSAGE_FD, false));
	}
	return (true);
}

void	restore_stdin_out(int *temp_std_fd)
{
	dup2(temp_std_fd[0], 0);
	dup2(temp_std_fd[1], 1);
	close(temp_std_fd[0]);
	close(temp_std_fd[1]);
}
