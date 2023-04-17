/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/10 21:20:51 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/04/10 21:20:51 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_list_to_arr(t_env_list *list)
{
	int			list_size;
	char		**ret;
	int			i;

	list_size = ft_lstsize((t_list *)list); //test
	ret = safe_alloc(sizeof(char *), list_size + 1);
	i = 0;
	while (i < list_size)
	{
		ret[i] = str_iple_join(list->key, "=", list->value);
		i++;
		list = list->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	add_list_node_from_env_variable(char *env_line, t_env_list **list)
{
	int		key_length;
	int		val_length;
	char	*key;
	char	*value;

	key_length = 0;
	val_length = 0;
	while (env_line[key_length] && env_line[key_length] != '=')
		key_length++;
	key = ft_substr(env_line, 0, key_length);
	if (!env_line[key_length])
		value = NULL;
	else
	{
		while (env_line[key_length + 1 + val_length])
			val_length++;
		value = ft_substr(env_line, key_length + 1, val_length);
	}
	add_env_node_to_list(list, key, value);
}
