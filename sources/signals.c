/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/30 19:01:09 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/04/30 19:01:09 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>

void	sigint_handler_generic(int signum)
{
	(void) signum;
	g_interrupted = 1;
}

void	sigint_handler_interactive(int signum)
{
	(void) signum;
	g_interrupted = 1;
}

void	sigint_handler_heredoc(int signum)
{
	(void) signum;
	g_interrupted = 1;
	ft_putchar_fd('\n', 1);
	rl_done = 1;
}
