/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   deprecated_functions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 18:55:49 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/04/20 18:55:49 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node_to_list(t_env_list **list, char *key, char *value)
{
	t_env_list	*last;
	t_env_list	*new;

	new = safe_alloc(sizeof(t_env_list), 1);
	if (!key)
		dprintf(2, "SUBSTRING ERROR IN ENVIR LIST");
	new->key = key;
	new->value = value;
	if (!*list)
		*list = new;
	else
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

static void	remove_node_and_remake_env(t_shell *shell, t_argument *args)
{
	t_env_list	*node;

	node = shell->environment;
	if (!ft_strcmp(args->content, node->key))
	{
		shell->environment = node->next;
	}
	while (node)
	{
		if (!ft_strcmp(args->content, node->key))
		{
			node->next = node->next->next;
			free(node->key);
			free(node->value);
			free(node);
			free_array(shell->envp);
			shell->envp = env_list_to_arr(shell->environment);
			return ;
		}
		node = node->next;
	}
}

static int	unset(t_argument *args, t_shell *shell);
{
	bool		err_occured;

	err_occured = false;
	while (args)
	{
		if (!str_is_fully_alnum(args->content))
		{
			dprintf(2, "you" C_RED "set" C_RESET "yourself up for failure\n\
					%s is not a valid identifier\n", args->content);
			err_occured = true;
		}
		else
			remove_node_and_remake_env(shell, args);
		args = args->next;
	}
	if (err_occured)
		return (1);
	return (0);
}

// old_export_alphabetize_part_which_is_just_strcmp()
// {
// 				if (copy[i][j] >= copy[i + 1][j])
// 			{
// 				if (copy[i][j] == copy[i + 1][j])
// 				{
// 					while(copy[i][j] == copy[i + 1][j]) //shouldnt have seg danger?
// 						j++;
// 					if (copy[i][j] <= copy[i + 1][j])
// 					{
// 						j = 0;
// 						i++;
// 						continue ;
// 					}
// 					j = 0;
// 				}
// }