/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array_init_testing.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 17:21:50 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/04/17 17:21:50 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//strcompares the cmd name to see if its a builtin and returns corresponding
// index, returns -1 on no index found

int	find_builtin_index(char *cmd)
{
	char	builtins[8][7];
	int		index;

	// builtins = safe_alloc(sizeof(char *), 8);
	builtins = (char [8][7]){"echo", "cd", "pwd", "export", "unset", "env", \
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

bool	single_builtin_executor(t_command *cmd, t_shell *shell)
{
	t_builtin_ptr	*builtins;
	int				i;
	int				temp_inout[2];

	i = find_builtin_index(cmd->target);
	if (i == -1)
		return (false);
	builtins = safe_alloc(sizeof(t_builtin_ptr), 6);
	*builtins = (t_builtin_ptr){&echo, &cd, &pwd, &export, &env, &exit};
	if (cmd->redirects)
		setup_single_builtin_redirects(cmd, temp_inout);
	builtins[i](cmd->arg_array[0], shell);
	free(builtins);
	if (cmd->redirects)
		return_single_builtin_redirects(temp_inout);
	return (true);
}

bool	single_builtin_executor(t_command *cmd, t_shell *shell)
{
	int		temp_inout[2];
	int		builtin_nbr;

	builtin_nbr = find_builtin_index(cmd->target);
	if (builtin_nbr == -1)
		return (false);
	if (cmd->redirects)
		setup_single_builtin_redirects(cmd->target, temp_inout);
	if (builtin_nbr == 0)
		echo(cmd->arg_array, shell); //arg arr not setup yet, either call arr setup or use t_arguments
	if (builtin_nbr == 1)
			cd(cmd->arg_array, shell);
	if (builtin_nbr == 2)
			pwd();
	if (builtin_nbr == 3)
			export
	if (builtin_nbr == 4)

	if (builtin_nbr == 5)

	if (builtin_nbr == 6)

	if (cmd->redirects)
		return_single_builtin_redirects(temp_inout);
	return (true);
}

int	find_builtin_index(char *cmd)
{
	const char	*builtins[8];
	int		index;

	index = 0;
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	while (builtins[index])
	{
		if (ft_strcmp(cmd, builtins[index]) == 0)
		{
			return (index);
		}
	}
	return (-1);
}