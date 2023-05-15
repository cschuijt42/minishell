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
	int	exit_val;

	(void)shell;
	exit_val = 0;
	printf("exit\n");
	if (args && args->content)
	{
		if (!is_valid_nbr_str(args->content))
		{
			dprintf(2, "%s: You can only exit with numbers >:(", args->content);
			exit_val = 255;
		}
		else
			exit_val = ft_atoi(args->content);
	}
	exit(exit_val);
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
