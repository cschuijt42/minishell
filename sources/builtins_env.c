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

int	parse_export_node(t_shell *shell, t_argument *arg, int ret_val)
{
	char		*env_str;
	t_env_list	*node;

	env_str = arg->content;
	while (*env_str && *env_str != '=' && ft_isalnum(*env_str))
		env_str++;
	if (*env_str && *env_str != '=')
	{
		return (print_error_message_export(arg->content, 1));
	}
	node = env_line_to_node(arg->content);
	add_env_var(node->key, node->value, shell);
	if (ft_strcmp(node->key, "PATH") == 0)
		regenerate_path_array(shell);
	free_node(node);
	return (ret_val);
}

int	export(t_argument *args, t_shell *shell)
{
	int			ret_val;

	ret_val = 0;
	if (!args)
		print_2d_array_alphabetically(shell->envp);
	while (args)
	{
		ret_val = parse_export_node(shell, args, ret_val);
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
