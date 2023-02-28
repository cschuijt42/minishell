/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/26 22:42:52 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/02/26 22:42:52 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <lexing.h>
#include <parsing.h>
#include "libft.h"

t_command	*build_command_tree(t_lexnode *input)
{
	t_command	*command_tree;
	t_command	*current_node;
	t_lexnode	*current_lexed;

	current_lexed = input;
	while (current_lexed)
	{
		current_node = build_command_node(&current_lexed);
		add_command_node_to_tree(current_node, &command_tree);
	}
	return (command_tree);
}

t_command	*build_command_node(t_lexnode **input)
{
	t_command	*command_node;
	int			loose_text_nodes;

	if (!(*input))
		temp_error("No more tokens after pipe");
	command_node = ft_calloc(1, sizeof(t_command));
	loose_text_nodes = 0;
	while (*input && (*input)->token_type != token_pipe)
	{
		if ((*input)->token_type == token_plain_text)
		{
			if (loose_text_nodes == 0)
				command_node->target = ft_strdup((*input)->value);
			else
				add_argument_to_command_node(*input, command_node);
			loose_text_nodes++;
			*input = (*input)->next;
		}
		else
			add_redirect_to_command_node(input, command_node);
	}
	return (command_node);
}

void	add_command_node_to_tree(t_command *new_command, t_command **tree)
{
	t_command	*last_command;

	if (!(*tree))
		*tree = new_command;
	else
	{
		last_command = *tree;
		while (last_command->next)
			last_command = last_command->next;
		last_command->next = new_command;
		new_command->prev = last_command;
	}
}

void	add_argument_to_command_node(t_lexnode *lexnode, t_command *command)
{
	t_argument	*last_arg;
	t_argument	*new_arg;

	new_arg = ft_calloc(1, sizeof(t_argument));
	new_arg->content = ft_strdup(lexnode->value);
	if (command->arguments == NULL)
		command->arguments = new_arg;
	else
	{
		last_arg = command->arguments;
		while (last_arg->next)
			last_arg = last_arg->next;
		last_arg->next = new_arg;
	}
}

void	add_redirect_to_command_node(t_lexnode **lexnode, t_command *command)
{
	t_redirect	*last_redirect;
	t_redirect	*new_redirect;

	// This check happens before anything is allocated so cleaning up
	// the tree should be easy enough from here
	if (!(*lexnode)->next || (*lexnode)->next->token_type != token_plain_text)
		temp_error("No text token after redirect");
	new_redirect = ft_calloc(1, sizeof(t_argument));
	new_redirect->type = (*lexnode)->token_type;
	new_redirect->target = (*lexnode)->next->value;
	if (command->redirects == NULL)
		command->redirects = new_redirect;
	else
	{
		last_redirect = command->redirects;
		while (last_redirect->next)
			last_redirect = last_redirect->next;
		last_redirect->next = new_redirect;
	}
	*lexnode = (*lexnode)->next->next;
}
