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

int	env(t_argument *args, t_shell *shell)
{
	t_env_list	*node;

	(void) args;
	node = shell->env_list;
	while (node)
	{
		if (node->value)
			printf("%s = %s\n", node->key, node->value);
		node = node->next;
	}
	return (0);
}

int	print_error_message_export(char *identifier, int return_value)
{
	dprintf(2, "%sError:\n'%s' is not a valid identifier%s\n", \
			C_RED, identifier, C_RESET);
	return (return_value);
}

int	export(t_argument *args, t_shell *shell)
{
	int			ret_val;
	t_env_list	*node;
	char		*env_str;

	ret_val = 0;
	if (!args)
		print_2d_array_alphabetically(shell->envp);
	while (args)
	{
		env_str = args->content;
		while (*env_str && *env_str != '=' && ft_isalnum(*env_str))
			env_str++;
		if (*env_str && *env_str != '=')
		{
			ret_val = print_error_message_export(args->content, 1);
			args = args->next;
			continue ;
		}
		node = env_line_to_node(args->content);
		add_env_var(node->key, node->value, shell);
		free_node(node);
		args = args->next;
	}
	regenerate_env_array(shell);
	return (ret_val);
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
			print_error_message_export(args->content, 1);
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
