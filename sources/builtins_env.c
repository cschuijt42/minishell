/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 18:47:19 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/05/08 18:47:19 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_alphabet(char **envp)
{
	int		i;
	int		arrlen;
	char	**copy;

	i = 0;
	arrlen = ptrarr_len((void **)envp);
	copy = safe_alloc(sizeof(char *), arrlen);
	ft_memcpy(copy, envp, sizeof(char *) * arrlen);
	while (arrlen)
	{
		while (copy[i + 1] && i + 1 < arrlen)
		{
			if (ft_strcmp(copy[i], copy[i + 1]) > 0)
				str_switch(&copy[i], &copy[i + 1]);
			i++;
		}
		arrlen--;
		i = 0;
	}
	print_2d_charray(copy);
	free(copy);
}

int	export(t_argument *args, t_shell *shell)
{
	if (!args)
		print_alphabet(shell->envp); //sort alphabetically?
	else if (!ft_strchr(args->content, (int) '='))
	{
		puts("placeholder"); //can put
	}
	return (0);
}

int	env(t_argument *args, t_shell *shell)
{
	(void)args;
	(void)shell;
	print_2d_charray(shell->envp);
	return (0);
}
//ok so, cd both starting with dir names and ./dirname should function the same
// ./../ is possible though!

// bash cd doesnt go into hidden directories nice
// cd blank space/with no args goes to home folder??

// https://man7.org/linux/man-pages/man1/cd.1p.html
