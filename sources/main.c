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

t_shell	*initialize_shell_struct(char **envp);
int		clean_up_shell_struct(t_shell *shell);

int	interrupted_on_readline(t_shell *shell)
{
	g_interrupted = 0;
	shell->return_value = 130;
	return (0);
}

int	run_interactive_mode(t_shell *shell)
{
	char	*input;

	signal(SIGINT, sigint_handler_interactive);
	input = readline(SHELL_PROMPT);
	signal(SIGINT, sigint_handler_generic);
	if (g_interrupted)
		return (interrupted_on_readline(shell));
	else if (!input)
	{
		printf("exit\n");
		return (1);
	}
	lexer(shell, input);
	if (shell->error_value == error_continue)
		build_command_tree(shell);
	if (shell->error_value == error_continue && shell->command_tree)
		executor(shell);
	if (shell->error_value != error_continue)
		print_error_value(shell->error_value);
	if (ft_strlen(input))
		add_history(input);
	free(input);
	clean_up_execution(shell);
	return (0);
}

void	run_single_command_mode(t_shell *shell, char *input)
{
	signal(SIGINT, sigint_handler_generic);
	if (!input)
	{
		printf("exit\n");
		return ;
	}
	lexer(shell, input);
	if (shell->error_value == error_continue)
		build_command_tree(shell);
	if (shell->error_value == error_continue && shell->command_tree)
		executor(shell);
	if (shell->error_value != error_continue)
		print_error_value(shell->error_value);
	clean_up_execution(shell);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	rl_getc_function = getc;
	shell = initialize_shell_struct(envp);
	using_history();
	g_interrupted = 0;
	signal(SIGQUIT, SIG_IGN);
	if (ac == 3 && !ft_strncmp(av[1], "-c", 3))
		run_single_command_mode(shell, av[2]);
	else
	{
		while (1)
		{
			if (run_interactive_mode(shell))
				break ;
		}
	}
	rl_clear_history();
	return (clean_up_shell_struct(shell));
}
