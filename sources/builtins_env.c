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

#define UNSET_ERR "\x1b[38;2;255;0;0myou've\x1b[38;2;255;128;0m\x1b[1m set \
\x1b[0m\x1b[38;2;255;0;0myourself up for failure \x1b[38;2;255;255;0m\n\"%s\"\
\x1b[38;2;255;0;0m is not a valid identifier\n\x1b[0m"

void	print_2d_array_alphabetically(char **envp)
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

int	env(t_argument *args, t_shell *shell)
{
	t_env_list	*node;

	node = shell->env_list;
	while (node)
	{
		if (node->value)
			printf("%s = %s\n", node->key, node->value);
		node = node->next;
	}
	return (0);
}

int	export(t_argument *args, t_shell *shell)
{
	int	ret_val;
	int	i;

	ret_val = 0;
	i = 0;
	if (!args)
	{
		print_2d_array_alphabetically(shell->envp);
		return (ret_val);
	}
	while (args)
	{
		while (args->content[i] && args->content[i])
		{

		}
		if (!ft_strchr(args->content, (int) '='))
		{
		}
		args = args->next;
	}
	return (0);
}

int	unset(t_argument *args, t_shell *shell)
{
	t_env_list	*node;
	bool		err_occured;

	err_occured = false;
	while (args)
	{
		if (!str_is_fully_alnum(args->content))
		{
			dprintf(2, UNSET_ERR, args->content);
			err_occured = true;
		}
		else
		{
			node = find_env_var(args->content, shell);
			if (node)
				remove_node_and_remake_env(node, shell);
		}
		args = args->next;
	}
	if (err_occured)
		return (1);
	return (0);
}

//ok so, cd both starting with dir names and ./dirname should function the same
// ./../ is possible though!

// bash cd doesnt go into hidden directories nice
// cd blank space/with no args goes to home folder??

// https://man7.org/linux/man-pages/man1/cd.1p.html
