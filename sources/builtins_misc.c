/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_misc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 18:49:30 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/05/08 18:49:30 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_argument *args, t_shell *shell)
{
	(void)shell; //do we have to free before exiting?
	printf("exit\n");
	if (args && args->content)
		exit(ft_atoi(args->content)); //custom atoi that protects against >230 overflow?
	exit(10);
}

int	echo(t_argument *args, t_shell *shell)
{
	bool	print_nl;

	print_nl = true;
	(void)shell;
	if (args && args->content)
	{
		if (!ft_strcmp(args->content, "-n"))
		{
			print_nl = false;
			args = args->next;
		}
		while (args->next)
		{
			printf("%s ", args->content);
			args = args->next;
		}
		if (args)
			printf("%s", args->content);
	}
	if (print_nl)
		printf("\n");
	return (0);
}

