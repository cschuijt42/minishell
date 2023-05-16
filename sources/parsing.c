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

t_command	*build_command_node(t_lexnode **input, t_shell *shell);
void		add_command_node_to_tree(t_command *new_command, t_command **tree);
void		add_argument_to_command_node(t_lexnode *lexnode, \
											t_command *command);
void		add_redirect_to_command_node(t_lexnode **lexnode, \
											t_command *command, t_shell *shell);

// Walks through the lexer output, constructing the
// command tree as it goes. If a command node is added
// without any contents, a pipe error should be thrown.
// Place to add error management later on!
void	build_command_tree(t_shell *shell)
{
	t_command	*current_node;
	t_lexnode	*current_lexed;

	current_lexed = shell->lexer_output;
	if (current_lexed && current_lexed->token_type == token_pipe)
	{
		shell->error_value = error_loose_pipe;
		return ;
	}
	while (current_lexed)
	{
		if (shell->error_value != error_continue)
			break ;
		if (current_lexed->token_type == token_pipe)
			current_lexed = current_lexed->next;
		current_node = build_command_node(&current_lexed, shell);
		add_command_node_to_tree(current_node, &(shell->command_tree));
		if (!(current_node->arguments) && !(current_node->target) && \
			!(current_node->redirects))
		{
			if (shell->error_value == error_continue)
				shell->error_value = error_empty_command_node;
			return ;
		}
	}
}

// Builds a single command node, with all its redirects and arguments,
// moving the lexnode pointer to the pipe or end of the lexer output.
t_command	*build_command_node(t_lexnode **input, t_shell *shell)
{
	t_command	*command_node;
	int			loose_text_nodes;

	command_node = safe_alloc(1, sizeof(t_command));
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
			add_redirect_to_command_node(input, command_node, shell);
		if (shell->error_value != error_continue)
			break ;
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

	new_arg = safe_alloc(1, sizeof(t_argument));
	new_arg->content = ft_strdup(lexnode->value);
	if (!(new_arg->content))
		exit(print_error_message_perror("malloc error", 1));
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
void	add_redirect_to_command_node(t_lexnode **lexnode, t_command *command, \
										t_shell *shell)
{
	t_redirect	*last_redirect;
	t_redirect	*new_redirect;

	if (!(*lexnode)->next || (*lexnode)->next->token_type != token_plain_text)
	{
		shell->error_value = error_loose_redirect_token;
		return ;
	}
	new_redirect = safe_alloc(1, sizeof(t_redirect));
	new_redirect->type = (*lexnode)->token_type;
	new_redirect->target = ft_strdup((*lexnode)->next->value);
	if (!new_redirect->target)
		exit(print_error_message_perror("malloc error", 1));
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
