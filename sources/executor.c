/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 15:29:39 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/03/22 15:29:39 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

// Loop over redirects in order of appearance, setting them up one by one.
// It is okay if one overrides another, as long as that results in all 
// relevant file descriptors being closed.
void	setup_command_redirects(t_command *command)
{
	t_redirect	*redirect;

	redirect = command->redirects;
	while (redirect)
	{
		if (redirect->type == redirect_input)
			setup_input_redirect(command, redirect); // Write this
		else if (redirect->type == redirect_output)
			setup_output_redirect(command, redirect, 0); // Write this
		else if (redirect->type == redirect_output_append)
			setup_output_redirect(command, redirect, 1); // Write this
		else
			setup_heredoc_redirect(command, redirect); // Write this
		redirect = redirect->next;
	}
}

// Program name expander, should loop over all PATH locations until we
// find a valid executable to run. If the target contains a slash character,
// we know the we're dealing with an absolute/relative path and can just
// copy that to command->target_expanded instead.
// When executing, we always use command->target_expanded.
void	expand_command_target(t_shell *shell, t_command *command)
{
	char	*target_prefix;

	if (ft_strchr(command->target, "/"))
		command->target_expanded = ft_strdup(command->target);
	else
	{
		// PATH matching until we find the right executable
		// Save eventual absolute path in command->target_expanded
		// Error out if we can't find a match?
	}
}

// Function to close the current and future commands' heredocs, to
// prevent them from hanging with other child processes.
// Every heredoc is a pipe open on the reading end. To prevent these
// pipes from living longer than necessary, any process they don't
// belong to should close them in advance.
// We assume previous heredoc pipes have already been closed in the loop.
void	clean_up_heredocs(t_command *command)
{
	while (command)
	{
		if (command->heredoc_pipe)
			close(command->heredoc_pipe[0]);
		command = command->next;
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
void	setup_child_process(t_shell *shell, t_command *command)
{
	char	**arguments;

	command->pid = fork();
	if (command->pid == -1)
		error_exit("Fork error", 1);
	if (command->pid)
		return ;
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
	setup_redirects(command);
	// Setup argument array here.
	expand_command_target(shell, command);
	clean_up_heredocs(command);
	execve(command->target_expanded, arguments, shell->envp);
	error_exit("Exec fail", 127);
}

// Main loop. For each command, an out-pipe is created if there is
// another command to pipe to. Pipes are stored in the command struct,
// on the command they are piping out of. Once a pipe is no longer needed,
// it is closed here for the main process, like a heredoc pipe for a process
// that has already been forked or a pipe between two processes that have
// already been forked. At the very end, the last remaining pipe is closed.
void	executor(t_shell *shell)
{
	t_command	*command;

	command = shell->command_tree;
	while (command)
	{
		if (command->next)
		{
			if (pipe(command->pipe_out))
				error_exit("Pipe failure", 1);
		}
		setup_child_process(shell, command);
		if (command->heredoc_pipe)
		{
			close(command->heredoc_pipe[0]);
		}
		if (command->prev)
		{
			close(command->prev->pipe_out[0]);
			close(command->prev->pipe_out[1]);
		}
		command = command->next;
	}
}
