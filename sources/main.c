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

#include "h_colors.h"
#include <stdio.h>
#include <stdlib.h>
#include "lexing.h"
#include <readline/readline.h>
#include <readline/history.h>

void	print_tokens(t_lexnode *list)
{
	while (list)
	{
		printf("%s\n", list->value);
		list = list->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_lexnode	*token_list;

	(void) argc;
	(void) argv;
	(void) envp;
	input = readline("\x1b[38;2;0;255;0mFROGGYSHELL:\x1b[0m");
	if (!input)
		temp_error("readline fail");
	token_list = lexer(input);
	print_tokens(token_list);
	return (0);
}
