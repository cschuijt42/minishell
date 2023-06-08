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
			printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	return (0);
}

static bool	is_valid_export_unset_input(char *str)
{
	if (!str || (!ft_isalpha(*str) && *str != '_'))
		return (false);
	while (*str && *str != '=' && (ft_isalnum(*str) || *str == '_'))
		str++;
	if (*str && *str != '=')
		return (false);
	return (true);
}

static int	parse_export_node(t_shell *shell, t_argument *arg)
{
	t_env_list	*node;

	if (!is_valid_export_unset_input(arg->content))
		return (print_error_message_export(arg->content, 1));
	node = env_line_to_node(arg->content);
	if (node->value || !find_env_var(node->key, shell))
	{
		add_env_var(node->key, node->value, shell);
		if (ft_strcmp(node->key, "PATH") == 0)
			regenerate_path_array(shell);
	}
	free_node(node);
	return (0);
}

int	export(t_argument *args, t_shell *shell)
{
	int			ret_val;

	ret_val = 0;
	if (!args)
		export_print_mode(shell->env_list);
	while (args)
	{
		ret_val = parse_export_node(shell, args);
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
		if (!is_valid_export_unset_input(args->content))
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
