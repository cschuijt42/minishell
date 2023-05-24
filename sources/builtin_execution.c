/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_execution.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 16:28:40 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/10 16:28:40 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

bool	single_builtin_executor(t_command *cmd, t_shell *shell)
{
	const t_builtin_ptr	builtins[] = {&echo, &cd, &pwd, &export, &unset, &env, \
									&builtin_exit};
	int					temp_inout[2];
	int					builtin_index;

	if (!cmd->target)
		return (false);
	builtin_index = find_builtin_index(cmd->target);
	if (builtin_index == -1)
		return (false);
	if (backup_stdin_out(temp_inout))
	{
		if (!g_interrupted && setup_command_redirects_builtin(cmd))
			shell->return_value = \
							builtins[builtin_index](cmd->arguments, shell);
		restore_stdin_out(temp_inout);
	}
	if (cmd->heredoc_pipe[0])
		close(cmd->heredoc_pipe[0]);
	return (true);
}

void	exec_if_builtin(t_command *cmd, t_shell *shell)
{
	const t_builtin_ptr	builtins[] = {&echo, &cd, &pwd, &export, &unset, &env, \
									&builtin_exit};
	int					i;

	i = find_builtin_index(cmd->target);
	if (i == -1)
		return ;
	exit(builtins[i](cmd->arguments, shell));
}

int	find_builtin_index(char *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", \
								"exit", NULL};
	int			index;

	index = 0;
	while (builtins[index])
	{
		if (ft_strcmp(cmd, builtins[index]) == 0)
			return (index);
		index++;
	}
	return (-1);
}
