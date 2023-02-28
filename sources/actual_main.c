/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actual_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 20:09:42 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/02/28 20:09:42 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;

	using_history();
	while (1)
	{
		input = readline(SHELL_PROMPT);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		// Lexer, parser, executor
		if (ft_strlen(input) && input[0] != ' ')
			add_history(input);
		free(input);
	}
	rl_clear_history();
	// Replace with return value later
	return (0);
}
