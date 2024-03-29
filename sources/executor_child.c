/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_child.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 20:11:50 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/04 20:11:50 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

// Loop over redirects in order of appearance, setting them up one by one.
// It is okay if one overrides another, as long as that results in all
// relevant file descriptors being closed.
void	setup_command_redirects_child(t_command *command)
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
			exit(print_error_message_perror("can't access infile", 1));
		else if (return_value == error_cant_open_infile)
			exit(print_error_message_perror("can't open infile", 1));
		else if (return_value == error_cant_access_outfile)
			exit(print_error_message_perror("can't access outfile", 1));
		else if (return_value == error_cant_dup_fd)
			exit(print_error_message_perror(ERROR_MESSAGE_FD, 1));
	}
}

int	expand_through_split_path(t_shell *shell, t_command *command)
{
	size_t	i;
	char	*path_match;

	i = 0;
	while (shell->split_path[i])
	{
		path_match = protected_str_iple_join(shell->split_path[i], \
									"/", command->target);
		if (access(path_match, F_OK | X_OK) == 0)
		{
			command->target_expanded = path_match;
			return (1);
		}
		free(path_match);
		i++;
	}
	return (0);
}

// Program name expander, should loop over all PATH locations until we
// find a valid executable to run. If the target contains a slash character,
// we know the we're dealing with an absolute/relative path and can just
// copy that to command->target_expanded instead.
// When executing, we always use command->target_expanded.
void	expand_command_target(t_shell *shell, t_command *command)
{
	if (ft_strchr(command->target, '/'))
	{
		command->target_expanded = command->target;
		return ;
	}
	if (shell->split_path[0] == NULL)
	{
		command->target_expanded = protected_str_iple_join(shell->cwd, \
														"/", command->target);
		return ;
	}
	if (expand_through_split_path(shell, command))
		return ;
	print_error_message_exit("no executable found", 127);
}

void	setup_command_pipes(t_command *command)
{
	if (command->prev)
	{
		dup2(command->prev->pipe_out[0], 0);
		close(command->prev->pipe_out[0]);
		close(command->prev->pipe_out[1]);
	}
	if (command->next)
	{
		dup2(command->pipe_out[1], 1);
		close(command->pipe_out[0]);
		close(command->pipe_out[1]);
	}
}

// Actual forking function. The PID gets saved into the command tree if
// we are in the main process, else we continue with the rest of this
// function:
// - If there is a previous command, set up the in-pipe.
// - If there is a next command, set up the out-pipe.
// - Set up any redirects we may have to work through, possibly
//   overriding pipes.
// - Expand the command name to a full path if necessary.
// - Set up an array of arguments with the original program name (TODO)
// - Execve time!
int	setup_child_process(t_shell *shell, t_command *command)
{
	command->pid = fork();
	if (command->pid == -1)
		return (print_error_message_perror("fork error", 1));
	if (command->pid)
		return (0);
	setup_command_pipes(command);
	if (!g_interrupted)
		setup_command_redirects_child(command);
	clean_up_heredocs(command);
	if (!command->target)
		exit(0);
	if (!ft_strlen(command->target))
		print_error_message_exit("no executable found", 127);
	exec_if_builtin(command, shell);
	setup_arg_array(command);
	expand_command_target(shell, command);
	if (g_interrupted)
		exit(130);
	signal(SIGQUIT, SIG_DFL);
	execve(command->target_expanded, command->arg_array, shell->envp);
	exit(print_error_message_perror("exec fail", 127));
	return (0);
}
