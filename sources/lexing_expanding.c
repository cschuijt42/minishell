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
#include "libft.h"
#include "lexing.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

void	expand_variable_in_quotes(char *var_name, t_lexnode **token_list)
{
	char	*var_value;

	var_value = value_for_variable(var_name);
	add_nested_node_to_lexer_output(var_value, token_plain_text, token_list);
	free(var_value);
}

void	expand_variable(char *var_name, t_lexnode **token_list, int i)
{
	char	*var_value;
	int		start;

	var_value = value_for_variable(var_name);
	start = i;
	while (var_value[i] && !is_whitespace(var_value[i]))
		i++;
	add_nested_node_to_lexer_output(ft_substr(var_value, start, i - start), \
									token_plain_text, token_list);
	i = skip_whitespace(var_value, i);
	if (var_value[i])
	{
		add_node_to_lexer_output(ft_strdup(""), token_plain_text, token_list);
		expand_variable(var_name, token_list, i);
	}
}
