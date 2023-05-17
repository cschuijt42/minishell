/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_recreation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 16:50:40 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/16 16:50:40 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	regenerate_env_array(t_shell *shell)
{
	if (shell->envp)
		free_array((void **)shell->envp);
	shell->envp = env_list_to_arr(shell->env_list);
}

void	update_shell_level(t_shell *shell)
{
	char	*lvl_str;
	int		lvl;

	lvl_str = get_env_var_value("SHLVL", shell->env_list);
	if (!lvl_str || !ft_isdigit_str(lvl_str))
		add_env_var("SHLVL", "1", shell);
	else
	{
		lvl = ft_atoi(lvl_str) + 1;
		lvl_str = ft_itoa(lvl);
		if (!lvl_str)
			print_error_message_perror("malloc fail :(", 1);
		add_env_var("SHLVL", lvl_str, shell);
		free(lvl_str);
	}
}
