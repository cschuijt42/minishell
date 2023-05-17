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
