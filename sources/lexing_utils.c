/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexing_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 19:05:10 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/03/01 19:05:10 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "h_colors.h"
#include <stdio.h>
#include <stdlib.h>

int	is_text_mode_change(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '|' || \
		c == '>' || c == '<' || c == '\0')
	{
		return (1);
	}
	else if (c == '\'' || c == '"')
		return (2);
	else if (c == '$')
		return (3);
	else
		return (0);
}

int	skip_whitespace(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	return (i);
}

void	add_node_to_lexer_output(char *content, int token_type, t_shell *shell)
{
	t_lexnode	*new_node;
	t_lexnode	*last_node;

	new_node = ft_calloc(1, sizeof(t_lexnode));
	new_node->token_type = token_type;
	new_node->value = content;
	if (!(shell->lexer_output))
		shell->lexer_output = new_node;
	else
	{
		last_node = shell->lexer_output;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

void	add_nested_node_to_lexer_output(char *content, int token_type, \
										t_shell *shell)
{
	t_lexnode	*new_node;
	t_lexnode	*last_node;

	new_node = ft_calloc(1, sizeof(t_lexnode));
	new_node->token_type = token_type;
	new_node->value = content;
	last_node = shell->lexer_output;
	while (last_node->next)
		last_node = last_node->next;
	while (last_node->tree_next)
		last_node = last_node->tree_next;
	last_node->tree_next = new_node;
}
