/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_printing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 15:39:52 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/17 15:39:52 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_2d_array_alphabetically(char **envp)
{
	int		i;
	int		arrlen;
	char	**copy;

	i = 0;
	arrlen = ptrarr_len((void **)envp) + 1;
	copy = safe_alloc(sizeof(char *), arrlen);
	ft_memcpy(copy, envp, sizeof(char *) * arrlen);
	while (arrlen)
	{
		while (i + 1 < arrlen && copy[i + 1])
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
