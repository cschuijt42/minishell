/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_struct.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 23:18:01 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/16 23:18:01 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*initialize_shell_struct(char **envp)
{
	t_shell	*shell;

	shell = safe_alloc(1, sizeof(t_shell));
	shell->cwd = safe_alloc(1, PATH_MAX);
	getcwd(shell->cwd, PATH_MAX);
	shell->return_value = 0;
	shell->env_list = parse_envp(envp);
	shell->envp = env_list_to_arr(shell->env_list);
	regenerate_path_array(shell);
	update_shell_level(shell);
	return (shell);
}

int	clean_up_shell_struct(t_shell *shell)
{
	int	return_value;

	return_value = shell->return_value;
	clean_up_lexer_output(shell);
	clean_up_command_tree(shell);
	clean_up_env_list(shell);
	free_array((void **) shell->envp);
	free_array((void **) shell->split_path);
	free(shell->cwd);
	free(shell);
	return (return_value);
}
