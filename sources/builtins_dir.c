/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_dir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 19:38:38 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/03/08 19:38:38 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

//changed from void to char * ret so it can be used internally, if u dont like
// it this way I can also just make 1 only for printing and put the instructions
// in cd
// 3/4 update.. yeah I might refactor this cause I can just call getcwd
int	pwd(t_argument *args, t_shell *shell)
{
	(void) args;
	if (!getcwd(shell->cwd, PATH_MAX))
	{
		perror("can't get working dir");
		return (1);
	}
	printf("%s\n", shell->cwd);
	return (0);
}

int	cd(t_argument *args, t_shell *shell)
{
	char	*new_dir;

	if (!getcwd(shell->cwd, PATH_MAX) || access(shell->cwd, F_OK) != 0)
	{
		perror(C_RED "current dir destroyed, I'm going HOME >:c\n" C_RESET);
		args = NULL;
	}
	if (!args)
	{
		new_dir = get_env_var_value("HOME", shell->env_list);
		if (!new_dir)
			return (print_error_message_return("HOME unset", 2));
	}
	else if (args->content && args->content[0] == '-' && !args->content[1])
	{
		new_dir = get_env_var_value("OLDPWD", shell->env_list);
		if (!new_dir)
			return (print_error_message_return("OLDPWD unset", 2));
	}
	new_dir = args->content;
	if (chdir(new_dir) == -1)
		return (print_error_message_perror("can't change directory", 1));
	// Change PWD and OLDPWD
	return (0);
}
