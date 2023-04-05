/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 17:21:15 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/03/06 17:21:15 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	add_env_node_to_list(t_env_list **list, char *key, char *value)
{
	t_env_list	*last;
	t_env_list	*new;

	if (!key || !value)
		dprintf(2, "SUBSTRING ERROR IN ENVIR LIST");
	new = ft_calloc(sizeof(t_env_list), 1);
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
	while (env_line[key_length + 1 + val_length])
		val_length++;
	value = ft_substr(env_line, key_length + 1, val_length);
	add_env_node_to_list(list, key, value);
}

t_env_list	*parse_envp(char **envp)
{
	int			i;
	t_env_list	*list;

	i = 0;
	list = NULL;
	while (envp[i])
	{
		add_list_node_from_env_variable(envp[i], &list);
		i++;
	}
	return (list);
}

char	*get_env_var_value(char *key, t_env_list *list)
{
	while (list && ft_strncmp(key, list->key, ft_strlen(key)))
		list = list->next;
	if (!list)
		return (NULL);
	return (list->value);
}

void	set_value(char *key, char *value, t_shell *shell)
{
	t_env_list	*env;

	env = shell->environment;
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			free(env->value);
			env->value = value;
		}
		env = env->next;
	}

}

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
