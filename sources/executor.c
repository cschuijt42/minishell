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

void	setup_command_redirects(t_command *command)
{
}

void	expand_command_target(t_shell *shell, t_command *command)
{
	char	*target_prefix;

	if (ft_strchr(command->target, "/"))
		command->target_expanded = ft_strdup(command->target);
	else
	{
		
	}
}

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
	expand_command_target(shell, command);
	execve(command->target_expanded, arguments, shell->envp);
	error_exit("Exec fail", 127);
}

void	close_last_pipe(t_command *command_tree)
{
	t_command	*last_with_pipe;

	if (!command_tree->next)
		return ;
	last_with_pipe = command_tree;
	while (last_with_pipe->next && last_with_pipe->next->next)
		last_with_pipe = last_with_pipe->next;
	close(last_with_pipe->pipe_out[0]);
	close(last_with_pipe->pipe_out[1]);
}

void	executor(t_shell *shell, char **envp)
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
			close(command->heredoc_pipe[1]);
		}
		if (command->prev)
		{
			close(command->prev->pipe_out[0]);
			close(command->prev->pipe_out[1]);
		}
		command = command->next;
	}
	close_last_pipe(shell->command_tree);
}
