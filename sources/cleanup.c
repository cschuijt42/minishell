/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 20:57:55 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/03/27 20:57:55 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up_lexer_output(t_lexnode *lexnodes)
{
	t_lexnode	*current;
	t_lexnode	*next;

	current = lexnodes;
	while (current)
	{
		free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
}

void	clean_up_redirect_list(t_redirect *redirects)
{
	t_redirect	*current;
	t_redirect	*next;

	current = redirects;
	while (current)
	{
		free(current->target);
		next = current->next;
		free(current);
		current = next;
	}
}

void	clean_up_argument_list(t_argument *arguments)
{
	t_argument	*current;
	t_argument	*next;

	current = arguments;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

void	clean_up_command_tree(t_command *command_tree)
{
	t_command	*current;
	t_command	*next;

	current = command_tree;
	while (current)
	{
		free(current->target);
		clean_up_argument_list(current->arguments);
		clean_up_redirect_list(current->redirects);
		next = current->next;
		free(current);
		current = next;
	}
}

void	clean_up_execution(t_shell *shell)
{
	clean_up_lexer_output(shell->lexer_output);
	clean_up_command_tree(shell->command_tree);
}
