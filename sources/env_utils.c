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
		ret[i] = protected_str_iple_join(list->key, "=", list->value);
		i++;
		list = list->next;
	}
	ret[i] = NULL;
	return (ret);
}


char	*get_env_var_value(char *key, t_env_list *list)
{
	while (list && ft_strncmp(key, list->key, ft_strlen(key)))
		list = list->next;
	if (!list)
		return (NULL);
	return (list->value);
}