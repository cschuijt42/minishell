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

void	set_value(char *key, char *value, t_shell *shell)
{
	t_env_list	*env;
	size_t		i;

	env = shell->env_list;
	i = 0;
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			free(env->value);
			env->value = value;
			free(shell->envp[i]);
			shell->envp[i] = protected_str_iple_join(env->key, "=", env->value);
		}
		env = env->next;
		i++;
	}
	if (ft_strcmp(key, "PATH") == 0)
		regenerate_path_array(shell);
}

t_env_list	*env_line_to_node(char *env_line)
{
	int			key_length;
	int			val_length;
	t_env_list	*node;

	key_length = 0;
	val_length = 0;
	node = safe_alloc(sizeof(t_env_list), 1);
	while (env_line[key_length] && env_line[key_length] != '=')
		key_length++;
	node->key = ft_substr(env_line, 0, key_length);
	if (!node->key)
		exit(print_error_message_perror("malloc error", 1));
	if (!env_line[key_length])
		node->value = NULL;
	else
	{
		while (env_line[key_length + 1 + val_length])
			val_length++;
		node->value = ft_substr(env_line, key_length + 1, val_length);
	}
	return (node);
}

t_env_list	*parse_envp(char **envp)
{
	int			i;
	t_env_list	*list;
	t_env_list	*head;

	list = env_line_to_node(envp[0]);
	i = 1;
	head = list;
	while (envp[i])
	{
		list->next = env_line_to_node(envp[i]);
		list = list->next;
		i++;
	}
	list->next = NULL;
	return (head);
}

void	remove_node_and_remake_env(t_env_list *remove_me, t_shell *shell)
{
	t_env_list	*current;

	current = shell->env_list;
	if (current != remove_me)
	{
		while (current->next != remove_me)
			current = current->next;
		current->next = current->next->next;
	}
	else
		shell->env_list = shell->env_list->next;
	free_node(remove_me);
	free_array((void **)shell->envp);
	shell->envp = env_list_to_arr(shell->env_list);
	regenerate_path_array(shell);
}

t_env_list	*find_env_var(char *key, t_shell *shell)
{
	t_env_list	*list;

	list = shell->env_list;
	while (list && ft_strcmp(key, list->key))
		list = list->next;
	if (list)
		return (list);
	return (NULL);
}
