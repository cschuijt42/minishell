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

	if (!key)
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
	size_t		i;

	env = shell->environment;
	i = 0;
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			free(env->value);
			env->value = value;
			free(shell->envp[i]);
			shell->envp[i] = str_iple_join(env->key, "=", env->value);
		}
		env = env->next;
		i++;
	}
}

