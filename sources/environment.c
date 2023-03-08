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

void	add_env_node_to_list(t_env_var **list, char *key, char *value)
{
	t_env_var	*last;
	t_env_var	*new;

	if (!key || !value)
		printf("SUBSTRING ERROR IN ENVIR LIST");
	new = ft_calloc(sizeof(t_env_var), 1);
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

void	add_list_node_from_env_variable(char *env_line, t_env_var **list)
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

t_env_var	*parse_envp(char **envp)
{
	int			i;
	t_env_var	*list;

	i = 0;
	list = NULL;
	while (envp[i])
	{
		add_list_node_from_env_variable(envp[i], &list);
		i++;
	}
	return (list);
}


char	*get_env_var_value(char *key, t_env_var *list)
{
	while (list && ft_strncmp(key, list->key, ft_strlen(key)))
		list = list->next;
	if (!list)
		return (NULL);
	return (list->value);
}
