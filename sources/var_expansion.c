/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.c                                    :+:    :+:            */
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

// t_env_var	*make_node(t_env_var **list, char *key, char *value)
// {
// 	if (!*list)
// 		*list = ft_calloc(sizeof(t_env_var), 1); //replace with protected malloc
// 	else
// 	{
// 		*list->next = ft_calloc(sizeof(t_env_var), 1); //ditto
// 		*list->next->prev = *list;
// 		*list = *list->next;
// 	}
// 	if (!key || !value)
// 		printf("SUBSTRING ERROR IN ENVIR *LIST");
// 	*list->key = key;
// 	*list->value = value;
// 	return (*list);
// }

// t_env_var	list_first(t_env_var *list)
// {
// 	while (list->prev)
// 		list = list->prev;
// }

t_env_var	*make_env_node(t_env_var *list, char *key, char *value)
{
	if (!list)
		list = ft_calloc(sizeof(t_env_var), 1); //replace with protected malloc
	else
	{
		while (list->next)
			list = list->next;
		list->next = ft_calloc(sizeof(t_env_var), 1); //ditto
		list = list->next;
	}
	if (!key || !value)
		printf("SUBSTRING ERROR IN ENVIR LIST");
	list->key = key;
	list->value = value;
	return (list);
}

void	add_env_var_to_list(char *env_line, t_env_var list)
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
	val_length = i;
	while (env_line[val_length])
		val_length++;
	value = ft_substr(env_line, key_length + 1, val_length);
	make_env_node(list, key, value);
}

t_env_var	*make_envir_list(char **envp)
{
	int			i;
	t_env_var	*list;

	i = 1;
	list = add_env_var_to_list(env[i], list);;
	while (envp[i])
	{
		add_env_var_to_list(env[i], list);
		printf("value = %s\n", list->value);
		printf("key %i = %s", i, list->key);
		i++;
	}
	return (list_first(list));
}


char	*get_env_value(char *key, t_envir_list *list)
{
	while (list && ft_strncmp(key, list->key, ft_strlen(key))) //replace w strcm[?]
		list = list->next;
	if (!list)
		return (NULL);
	return (list->value); //changed from strdup as asked ^^
}

//im assuming we wont ever have a line without =
