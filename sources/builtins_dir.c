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

int	pwd(t_argument *args, t_shell *shell)
{
	(void) args;
	if (!getcwd(shell->cwd, PATH_MAX))
	{
		return (print_error_message_perror("can't get working directory", 1));
	}
	printf("%s\n", shell->cwd);
	return (0);
}

int	change_directory(char *new_dir, t_shell *shell)
{
	if (chdir(new_dir) == -1)
		return (print_error_message_perror("can't change directory", 1));
	add_env_var("OLDPWD", get_env_var_value("PWD", shell->env_list), shell);
	getcwd(shell->cwd, PATH_MAX);
	add_env_var("PWD", shell->cwd, shell);
	return (0);
}

int	cd(t_argument *args, t_shell *shell)
{
	char	*new_dir;

	if (!getcwd(shell->cwd, PATH_MAX) || access(shell->cwd, F_OK) != 0)
	{
		print_error_message_return("current directory no longer exists", 0);
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
	else
		new_dir = args->content;
	return (change_directory(new_dir, shell));
}
