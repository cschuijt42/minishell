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

t_envir_var	*make_node(t_envir_var *list, char *key, char *value)
{
	if (!list)
		list = ft_calloc(sizeof(t_envir_var), 1); //replace with protected malloc
	else
	{
		list->next = ft_calloc(sizeof(t_envir_var), 1); //ditto
		list->next->prev = list;
		list = list->next;
	}
	if (!key || !value)
		printf("SUBSTRING ERROR IN ENVIR LIST");
	list->key = key;
	list->value = value;
	return (list);
}

t_envir_var	list_first(t_envir_var *list)
{
	while (list->prev)
		list = list->prev;
}

t_envir_var	*make_envir_list(char **envp)
{
	int			i;
	int			j;
	int			k;
	t_envir_var	*list;

	i = 0;
	j = 0;
	k = 0;
	list = NULL;
	while (envp[i])
	{
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		k = j;
		while (envp[i][k])
			k++;
		list = make_node(list, ft_substr(envp[i], 0, j), ft_substr(envp[i], j + 1, k));
		i++;
		j = 0;
		printf("value = %s\n", list->value);
		printf("key %i = %s", i, list->key);
	}
	return (list_first(list));
}

char	*get_env_value(char *key, t_envir_list *list)
{
	while (list && ft_strncmp(key, list->key, ft_strlen(key))) //replace w strcm[?]
		list = list->next;
	if (!list)
		return (NULL);
	return (ft_strdup(list->value));
}

//im assuming we wont ever have a line without =

int	main(int argc, char **argv, char **envp)
{
	// char	*env;

	// char *str = "HOME=GAMER\0";
	// envp = &str;
	// env = getenv("HOME");
	// printf("%s\n", env);
	// while (*envp)
	// {
	// 	printf("%s\n", *envp);
	// 	envp++;
	// }
	make_envir_list(envp);
	return (0);
}