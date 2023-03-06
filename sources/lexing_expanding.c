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

void	expand_variables(t_lexnode *token)
{
	t_lexnode	*current;
	t_lexnode	*current_nested;

	current = token;
	while (current)
	{
		if (current->tree_next)
		{
			current_nested = current->tree_next;
			while (current_nested)
			{
				if (current_nested->token_type == token_quoted_var)
					expand_variable_in_quotes(current_nested);
				else if (current_nested->token_type == token_unquoted_var)
					expand_variable_outside_quotes(current_nested, current);
				current_nested = current_nested->tree_next;
			}
		}
		current = current->next;
	}
}

void	expand_variable_in_quotes(t_lexnode *token)
{
	char	*var_value;
	int		i;

	var_value = value_for_variable(token->value);
	free(token->value);
	token->value = NULL;
	i = 0;
	while (var_value[i])
	{
		if (var_value[i] == '$' && (ft_isalnum(var_value[i + 1]) || \
									var_value[i + 1] == '_'))
		{
			
		}
		else
			i++;
	}
}
