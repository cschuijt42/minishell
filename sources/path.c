/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 21:50:22 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/03/27 21:50:22 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	regenerate_path_array(t_shell *shell)
{
	t_env_list	*path_variable;

	path_variable = shell->env_list;
	while (path_variable && ft_strncmp("PATH", path_variable->key, 5))
		path_variable = path_variable->next;
	if (shell->split_path)
		free_array((void **) shell->split_path);
	if (!path_variable)
		shell->split_path = safe_alloc(sizeof(char *), 1);
	else
		shell->split_path = ft_split(path_variable->value, ':');
	if (!shell->split_path)
		print_error_message_exit("malloc error", 1);
}
