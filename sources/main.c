/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:03:57 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/02/16 18:03:57 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "h_colors.h"
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "lexing.h"
#include "parsing.h"

int	g_return_value = 0;

void	print_tokens(t_lexnode *list)
{
	while (list)
	{
		printf("%d: [%s]\n", list->token_type, list->value);
		list = list->next;
	}
}

void	print_command_tree(t_command *command_tree)
{
	t_argument	*argument;
	t_redirect	*redirect;

	printf("%s%sCommand tree:%s\n\n", C_BOLD, C_RED, C_RESET);
	while (command_tree)
	{
		printf("%sCommand: %s%s%s\n", C_RESET, C_BOLD, C_ORANGE, \
										command_tree->target);
		printf("%sPiped from: %s%s%s\n", C_RESET, C_BOLD, C_YELLOW, \
					command_tree->prev ? command_tree->prev->target : "-");
		printf("%sPipes to: %s%s%s\n", C_RESET, C_BOLD, C_GREEN, \
					command_tree->next ? command_tree->next->target : "-");
		printf("%sArguments: ", C_RESET);
		argument = command_tree->arguments;
		while (argument)
		{
			printf("%s%s%s", C_BOLD, C_BLUE, argument->content);
			if (argument->next)
				printf("%s, ", C_RESET);
			argument = argument->next;
		}
		printf("\n%sRedirects: ", C_RESET);
		redirect = command_tree->redirects;
		while (redirect)
		{
			printf("%s%s", C_BOLD, C_VIOLET);
			if (redirect->type == redirect_input)
				printf("<");
			else if (redirect->type == redirect_heredoc)
				printf("<<");
			else if (redirect->type == redirect_output)
				printf(">");
			else if (redirect->type == redirect_output_append)
				printf(">>");
			printf(" %s", redirect->target);
			if (redirect->next)
				printf("%s, ", C_RESET);
			redirect = redirect->next;
		}
		printf("%s\n\n", C_RESET);
		command_tree = command_tree->next;
	}
}

// int	main(void)
// {
// 	char		*input;
// 	t_lexnode	*token_list;
// 	t_command	*command_tree;

// 	input = readline("\x1b[38;2;0;255;0mFROGGYSHELL:\x1b[0m ");
// 	if (!input)
// 		temp_error("readline fail");
// 	token_list = lexer(input);
// 	print_tokens(token_list);
// 	command_tree = build_command_tree(token_list);
// 	print_command_tree(command_tree);
// 	return (0);
// }

// void	add_token(t_lexnode **tokens, int type, char *content)
// {
// 	t_lexnode	*new_node;
// 	t_lexnode	*last_node;

// 	new_node = ft_calloc(1, sizeof(t_lexnode));
// 	new_node->token_type = type;
// 	if (content)
// 		new_node->value = ft_strdup(content);
// 	if (!(*tokens))
// 		*tokens = new_node;
// 	else
// 	{
// 		last_node = *tokens;
// 		while (last_node->next)
// 			last_node = last_node->next;
// 		last_node->next = new_node;
// 	}
// }

int	main(void)
{
	t_lexnode	*tokens;
	t_command	*command_tree;
	char		*input;

	using_history();
	while (1)
	{
		input = readline(SHELL_PROMPT);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		tokens = lexer(input);
		// print_tokens(tokens);
		command_tree = build_command_tree(tokens);
		print_command_tree(command_tree);
		if (ft_strlen(input))
			add_history(input);
		free(input);
	}
	// rl_clear_history();
	// Replace with return value later
	return (0);
}
