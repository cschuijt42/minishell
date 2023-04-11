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

bool	is_builtin(t_command *cmd, t_shell *shell)
{
	char	*name;

	name = cmd->target;
	if (!ft_strcmp(name, "cd"))
	{
		if (cmd->arguments)
			cd(cmd->arguments->content, shell);
		else
			cd(NULL, shell);
		return (true);
	}
	else if (!ft_strcmp(name, "pwd"))
	{
		pwd(true);
		return (true);
	}
	return (false);
}

built_