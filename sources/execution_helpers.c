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

typedef int	(*t_builtin_ptr)(char *, t_shell *);

int	builtin_index(char *cmd);
int	*setup_single_builtin_redirects(t_command *cmd);

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
	t_builtin_ptr	*builtins;
	int				i;
	int				*temp_std_fd;

	i = builtin_index(cmd->target);
	if (i == -1)
		return (false);
	builtins = safe_alloc(sizeof(t_builtin_ptr), 6);
	*builtins = (t_builtin_ptr){&echo, &cd, &pwd, &export, &env, &exit};
	if (cmd->redirects)
		temp_std_fd = setup_single_builtin_redirects(cmd->redirects);
	builtins[i](cmd->arg_array[0], shell);
	free(builtins);
	dup2(temp_std_fd[0], 0);
	dup2(temp_std_fd[1], 1);
	close(temp_std_fd[0]);
	close(temp_std_fd[1]);
	return (true);
}

int	*setup_single_builtin_redirects(t_command *cmd)
{
	int	temp_inout[2];

	temp_inout[0] = dup(0);
	temp_inout[1] = dup(1); //dup protection?
	setup_command_redirects(cmd);
	return (temp_inout);
}

//strcompares the cmd name to see if its a builtin and returns corresponding
// index, returns -1 on no index found
int	builtin_index(char *cmd)
{
	char	**builtins;
	int		index;

	builtins = safe_alloc(sizeof(char *), 8);
	*builtins = (char *){"echo", "cd", "pwd", "export", "unset", "env", \
						"exit", NULL};
	index = 0;
	while (builtins[index])
	{
		if (ft_strcmp(cmd, builtins[index]) == 0)
		{
			free(builtins);
			return (index);
		}
	}
	return (-1);
}

//builtin handler thoughts: I feel like the refactor should move the builtin
// index into the main function, and the last