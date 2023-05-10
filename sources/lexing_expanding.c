/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexing_expanding.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 00:06:07 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/03/06 00:06:07 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexing.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

void	expand_variable_in_quotes(char *var_name, t_shell *shell)
{
	char	*var_value;

	if (var_name[0] == '?')
		add_nested_node_to_lexer_output(ft_itoa(shell->return_value), \
										token_plain_text, shell);
	else
	{
		var_value = get_env_var_value(var_name, shell->environment);
		if (!var_value)
			return ;
		add_nested_node_to_lexer_output(ft_strdup(var_value), \
										token_plain_text, shell);
	}
}

void	expand_variable(char *var_name, t_shell *shell, int i)
{
	char	*var_value;
	int		start;

	if (var_name[0] == '?')
		add_nested_node_to_lexer_output(ft_itoa(shell->return_value), \
										token_plain_text, shell);
	else
	{
		var_value = get_env_var_value(var_name, shell->environment);
		if (!var_value)
			return ;
		start = i;
		while (var_value[i] && !is_whitespace(var_value[i]))
			i++;
		add_nested_node_to_lexer_output(ft_substr(var_value, start, i - start), \
										token_plain_text, shell);
		i = skip_whitespace(var_value, i);
		if (var_value[i])
		{
			add_node_to_lexer_output(ft_strdup(""), token_plain_text, shell);
			expand_variable(var_name, shell, i);
		}
	}
}
