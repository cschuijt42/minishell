/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_printing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 15:39:52 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/17 15:39:52 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_and_print_smallest_env_line(t_env_list *list);

void	export_print_mode(t_env_list *list)
{
	const t_env_list	*head = (const t_env_list *)list;
	t_env_list			*current_smallest;
	char				*last_printed;

	last_printed = find_and_print_smallest_env_line(list);
	while (1)
	{
		current_smallest = NULL;
		while (list)
		{
			if (ft_strcmp(last_printed, list->key) < 0 && (!current_smallest \
			|| ft_strcmp(current_smallest->key, list->key) > 0))
				current_smallest = list;
			list = list->next;
		}
		if (!current_smallest)
			return ;
		printf("%s", current_smallest->key);
		if (current_smallest->value)
			printf("=\"%s\"", current_smallest->value);
		printf("\n");
		last_printed = current_smallest->key;
		list = (t_env_list *)head;
	}
}

char	*find_and_print_smallest_env_line(t_env_list *list)
{
	t_env_list	*smallest;

	smallest = list;
	while (list)
	{
		if (ft_strcmp(smallest->key, list->key) > 0)
			smallest = list;
		list = list->next;
	}
	printf("%s", smallest->key);
	if (smallest->value)
		printf("=\"%s\"", smallest->key);
	printf("\n");
	return (smallest->key);
}

int	print_error_message_export(char *identifier, int return_value)
{
	dprintf(2, "%sError:\n'%s' is not a valid identifier%s\n", \
			C_RED, identifier, C_RESET);
	return (return_value);
}
