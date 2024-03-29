/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 21:30:04 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/05 21:30:04 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "h_colors.h"

void	print_message_for_error(int error_value)
{
	if (error_value == error_unclosed_quote)
		dprintf(2, "Unclosed quote in input");
	else if (error_value == error_loose_pipe)
		dprintf(2, "Loose pipe at start of input");
	else if (error_value == error_loose_redirect_token)
		dprintf(2, "Encountered redirect without target");
	else if (error_value == error_empty_command_node)
		dprintf(2, "Empty command node in tree (loose pipe?)");
	else
		dprintf(2, "Unknown error number %d", error_value);
}

void	print_error_value(int error_value)
{
	dprintf(2, "%sError:\n", C_RED);
	print_message_for_error(error_value);
	dprintf(2, "%s\n", C_RESET);
}

void	print_error_message_exit(char *message, int return_value)
{
	dprintf(2, "%sError:\n%s%s\n", C_RED, message, C_RESET);
	exit(return_value);
}

int	print_error_message_return(char *message, int return_value)
{
	dprintf(2, "%sError:\n%s%s\n", C_RED, message, C_RESET);
	return (return_value);
}

int	print_error_message_perror(char *message, int return_value)
{
	dprintf(2, "%sError: %s\n%s%s\n", C_RED, message, strerror(errno), C_RESET);
	return (return_value);
}
