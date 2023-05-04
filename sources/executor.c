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

#include "execution.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

// Main loop. For each command, an out-pipe is created if there is
// another command to pipe to. Pipes are stored in the command struct,
// on the command they are piping out of. Once a pipe is no longer needed,
// it is closed here for the main process, like a heredoc pipe for a process
// that has already been forked or a pipe between two processes that have
// already been forked. At the very end, the last remaining pipe is closed.
void	execute_commands(t_shell *shell)
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
		if (command->heredoc_pipe[0])
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

void	executor(t_shell *shell)
{
	t_command	*command;
	int			wstatus;

	if (g_interrupted)
	{
		shell->return_value = 130;
		return ;
	}
	setup_all_heredocs(shell);
	execute_commands(shell);
	command = shell->command_tree;
	while (command)
	{
		if (!command->pid)
			break ;
		waitpid(command->pid, &wstatus, 0);
		command = command->next;
	}
	if (WIFEXITED(wstatus))
		shell->return_value = WEXITSTATUS(wstatus);
	else
		shell->return_value = 128 + WTERMSIG(wstatus);
	printf("\nReturn value: %d\n", shell->return_value);
}
