/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
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
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void) argc;
	(void) argv;
	(void) envp;
	input = readline("\x1b[38;2;0;255;0mFROGGYSHELL:\x1b[0m");
	printf("input = %s\n", input);
	free(input);
	return (0);
}
