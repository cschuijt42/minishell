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

	exit_val = shell->return_value;
	printf("exit\n");
	if (args && args->content)
	{
		if (!is_valid_nbr_str(args->content))
		{
			print_error_message_return("You can only exit with numbers >:(", 0);
			exit_val = 255;
		}
		else
			exit_val = ft_atoi(args->content);
	}
	clean_up_shell_struct(shell);
	exit(exit_val);
}

int	echo(t_argument *args, t_shell *shell)
{
	bool	print_nl;

	print_nl = true;
	(void)shell;
	if (args && args->content)
	{
		while (args && !ft_strcmp(args->content, "-n"))
		{
			print_nl = false;
			args = args->next;
		}
		while (args && args->next)
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
