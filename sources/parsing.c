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

#include "lexing.h"
#include "parsing.h"
#include "libft.h"

t_command	*build_command_node(t_lexnode **input);
void		add_command_node_to_tree(t_command *new_command, t_command **tree);
void		add_argument_to_command_node(t_lexnode *lexnode, \
											t_command *command);
void		add_redirect_to_command_node(t_lexnode **lexnode, \
											t_command *command);

// Walks through the lexer output, constructing the
// command tree as it goes. If a command node is added
// without any contents, a pipe error should be thrown.
// Place to add error management later on!
t_command	*build_command_tree(t_lexnode *input)
{
	t_command	*command_tree;
	t_command	*current_node;
	t_lexnode	*current_lexed;

	command_tree = NULL;
	current_lexed = input;
	if (current_lexed && current_lexed->token_type == token_pipe)
		temp_error("Loose pipe at start of command");
	while (current_lexed)
	{
		if (current_lexed->token_type == token_pipe)
			current_lexed = current_lexed->next;
		current_node = build_command_node(&current_lexed);
		add_command_node_to_tree(current_node, &command_tree);
		if (!(current_node->arguments) && !(current_node->target) && \
			!(current_node->redirects))
			temp_error("Empty node in command tree (loose pipe?)");
	}
	return (command_tree);
}

// Builds a single command node, with all its redirects and arguments,
// moving the lexnode pointer to the pipe or end of the lexer output.
t_command	*build_command_node(t_lexnode **input)
{
	t_command	*command_node;
	int			loose_text_nodes;

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

// Adds a command node to the end of the tree, connecting the
// doubly linked list for pipe construction in the executor.
// Does not move the lexer pointer.
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

// Adds an argument to the given command node, duplicating the contents of
// the lexer node. Does not move the lexer pointer.
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

// Adds a redirect to the list of redirects of the given command node,
// duplicating the contents of the next (text) node in the lexer chain.
// If the next node is not text, an error is thrown
// TODO: clean up tree on error
void	add_redirect_to_command_node(t_lexnode **lexnode, t_command *command)
{
	t_redirect	*last_redirect;
	t_redirect	*new_redirect;

	// This check happens before anything is allocated so cleaning up
	// the tree should be easy enough from here
	if (!(*lexnode)->next || (*lexnode)->next->token_type != token_plain_text)
		temp_error("No text token after redirect");
	new_redirect = ft_calloc(1, sizeof(t_redirect));
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
