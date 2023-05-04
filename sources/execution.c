/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 15:43:52 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/03/20 15:43:52 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <unistd.h>

void	execute_command_tree(t_command *tree)
{
	pid_t		*pid_array;
	t_command	*current;

	current = tree;
	while (current)
	{
		current->pid = fork();
		if (current->pid == 0)
			execute_command(current);
		current = current->next;
	}
}

size_t	count_commannds(t_command *tree)
{
	t_command	*current;
	size_t		i;

	current = tree;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}
