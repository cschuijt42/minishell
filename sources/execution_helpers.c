/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution_helpers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 13:24:24 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/03/27 13:24:24 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

typedef void	(*t_builtin_ptr)(char **, t_shell *);

int		find_builtin_index(char *cmd);
void	setup_single_builtin_redirects(t_command *cmd, int *temp_inout);
void	return_single_builtin_redirects(int *temp_std_fd);

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
		if (command->heredoc_pipe[0])
			close(command->heredoc_pipe[0]);
		command = command->next;
	}
}

void	setup_arg_array(t_command *command)
{
	size_t		i;
	t_argument	*current;

	i = 2;
	current = command->arguments;
	while (current)
	{
		current = current->next;
		i++;
	}
	command->arg_array = safe_alloc(sizeof(char *), i);
	command->arg_array[0] = command->target;
	i = 1;
	current = command->arguments;
	while (current)
	{
		command->arg_array[i] = current->content;
		i++;
		current = current->next;
	}
}

bool	single_builtin_executor(t_command *cmd, t_shell *shell)
{
	const t_builtin_ptr	builtins[] = {&echo, &cd, &pwd, &export, &env, \
										&builtin_exit};
	int					temp_inout[2];
	int					builtin_index;

	builtin_index = find_builtin_index(cmd->target);
	if (builtin_index == -1)
		return (false);
	if (cmd->redirects)
		setup_single_builtin_redirects(cmd, temp_inout);
	setup_arg_array(cmd);
	builtins[builtin_index](cmd->arg_array, shell);
	if (cmd->redirects)
		return_single_builtin_redirects(temp_inout);
	return (true);
}

int	find_builtin_index(char *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", \
								"exit"};
	int			index;

	index = 0;
	while (builtins[index])
	{
		if (ft_strcmp(cmd, builtins[index]) == 0)
		{
			return (index);
		}
	}
	return (-1);
}

void	setup_single_builtin_redirects(t_command *cmd, int *temp_inout)
{
	temp_inout[0] = dup(0);
	temp_inout[1] = dup(1); //dup protection?
	setup_command_redirects(cmd);
}

void	return_single_builtin_redirects(int *temp_std_fd)
{
	dup2(temp_std_fd[0], 0);
	dup2(temp_std_fd[1], 1);
	close(temp_std_fd[0]);
	close(temp_std_fd[1]);
}
