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

#include <stdio.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	input = readline("FROGGYSHELL:");
	printf("input = %s\n",input);
	return (0);
}