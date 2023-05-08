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
	node->key = ft_substr(env_line, 0, key_length); //= substr exit, make diff version
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

	current = shell->environment;
	if (current != remove_me)
	{
		while (current->next != remove_me)
			current = current->next;
		current->next = current->next->next;
	}
	else
		shell->environment = remove_me->next;
	free(remove_me->key);
	free(remove_me->value);
	free(remove_me);
	free_array((void **)shell->envp);
	shell->envp = env_list_to_arr(shell->environment);
}

void	find_env_var(char *key, t_shell *shell)
{

	t_env_list	*list;

	list = shell->environment;
	while (list && ft_strncmp(key, list->key, ft_strlen(key)))
		list = list->next;
	if (list)
		remove_node_and_remake_env(list, shell);
} //wanted to finish but was getting too late, this could be 1 fun w the 1 above

int	unset(t_argument *args, t_shell *shell)
{
	t_env_list	*node;
	bool		err_occured;

	err_occured = false;
	while (args)
	{
		node = shell->environment;
		if (!str_is_fully_alnum(args->content))
		{
			dprintf(2, "you" C_RED "set" C_RESET "yourself up for failure\n\
					%s is not a valid identifier\n", args->content);
			err_occured = true;
		}
		else
		{
			while (node)
			{
				if (!ft_strcmp(args->content, node->key))
				{
					remove_node_and_remake_env(node, shell);
					break ; //could remove for more readablity but less performance
				}
				node = node->next;
			}
		}
		args = args->next;
	}
	if (err_occured)
		return (1);
	return (0);
}
