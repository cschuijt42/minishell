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

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "h_colors.h"
#include "minishell.h"
#include "lexing.h"
#include "parsing.h"

int	g_interrupted = 0;

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
		printf("\n%sRedirect: ", C_RESET);
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

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	char	*input;

	(void) ac;
	(void) av;
	shell = safe_alloc(1, sizeof(t_shell));
	shell->return_value = 0;
	shell->environment = parse_envp(envp);
	shell->envp = envp;
	regenerate_path_array(shell);
	using_history();
	g_interrupted = 0;
	rl_getc_function = getc;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, sigint_handler_interactive);
		input = readline(SHELL_PROMPT);
		signal(SIGINT, sigint_handler_generic);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		lexer(shell, input);
		shell->command_tree = build_command_tree(shell->lexer_output);
		executor(shell);
		if (ft_strlen(input))
			add_history(input);
		free(input);
		clean_up_execution(shell);
	}
	rl_clear_history();
	return (shell->return_value);
}
