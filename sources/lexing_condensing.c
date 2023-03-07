/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexing_condensing.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 15:55:28 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/03/05 15:55:28 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexing.h"

void	condense_lexer_output(t_lexnode **token_list)
{
	t_lexnode	*current_token;

	current_token = *token_list;
	while (current_token)
	{
		if (current_token->tree_next)
			condense_token(current_token);
		current_token = current_token->next;
	}
}

void	condense_token(t_lexnode *token)
{
	t_lexnode	*current_nested;
	t_lexnode	*next_nested;
	char		*temp;

	current_nested = token->tree_next;
	temp = NULL;
	while (current_nested)
	{
		temp = ft_strjoin(token->value, current_nested->value);
		free(token->value);
		token->value = temp;
		next_nested = current_nested->tree_next;
		free(current_nested->value);
		free(current_nested);
		current_nested = next_nested;
	}
}
