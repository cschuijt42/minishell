/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/28 12:30:51 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/03/28 12:30:51 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

void	cycle_heredoc_pipe(t_command *command)
{
	if (command->heredoc_pipe[0])
		close(command->heredoc_pipe[0]);
	if (pipe(command->heredoc_pipe))
		error_exit("Pipe error", 1);
}

void	setup_heredoc(t_command *command, t_redirect *heredoc, int i)
{
	char	*input;
	char	*prompt;

	if (g_interrupted)
		return ;
	cycle_heredoc_pipe(command);
	prompt = safe_alloc(sizeof(char), 15);
	sprintf(prompt, "heredoc[%d]>", i);
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		if (!ft_strcmp(input, heredoc->target))
		{
			free(input);
			break ;
		}
		ft_putendl_fd(input, command->heredoc_pipe[1]);
		free(input);
		if (g_interrupted)
			break ;
	}
	free(prompt);
	close(command->heredoc_pipe[1]);
}

void	setup_all_heredocs(t_shell *shell)
{
	t_command	*current_command;
	t_redirect	*current_redirect;
	int			i;

	signal(SIGINT, sigint_handler_heredoc);
	i = 1;
	current_command = shell->command_tree;
	while (current_command)
	{
		current_redirect = current_command->redirects;
		while (current_redirect)
		{
			if (current_redirect->type == redirect_heredoc)
			{
				setup_heredoc(current_command, current_redirect, i);
				i++;
			}
			current_redirect = current_redirect->next;
		}
		current_command = current_command->next;
	}
	signal(SIGINT, sigint_handler_generic);
}
