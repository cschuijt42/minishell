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

void	free_nested_lexer_output(t_lexnode *lexnode)
{
	t_lexnode	*current;
	t_lexnode	*next;

	current = lexnode;
	while (current)
	{
		if (current->value)
			free(current->value);
		next = current->tree_next;
		free(current);
		current = next;
	}
}

void	clean_up_lexer_output(t_shell *shell)
{
	t_lexnode	*current;
	t_lexnode	*next;

	current = shell->lexer_output;
	while (current)
	{
		if (current->tree_next)
			free_nested_lexer_output(current->tree_next);
		if (current->value)
			free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
	shell->lexer_output = NULL;
}

void	clean_up_argument_and_redirect_list(t_argument *arguments, \
											t_redirect *redirects)
{
	t_argument	*current_argument;
	t_argument	*next_argument;
	t_redirect	*current_redirect;
	t_redirect	*next_redirect;

	current_argument = arguments;
	while (current_argument)
	{
		free(current_argument->content);
		next_argument = current_argument->next;
		free(current_argument);
		current_argument = next_argument;
	}
	current_redirect = redirects;
	while (current_redirect)
	{
		if (current_redirect->target)
			free(current_redirect->target);
		next_redirect = current_redirect->next;
		free(current_redirect);
		current_redirect = next_redirect;
	}
}

void	clean_up_command_tree(t_shell *shell)
{
	t_command	*current;
	t_command	*next;

	current = shell->command_tree;
	while (current)
	{
		free(current->target);
		clean_up_argument_and_redirect_list(current->arguments, \
											current->redirects);
		next = current->next;
		free(current);
		current = next;
	}
	shell->command_tree = NULL;
}

void	clean_up_execution(t_shell *shell)
{
	clean_up_lexer_output(shell);
	clean_up_command_tree(shell);
	g_interrupted = 0;
}
