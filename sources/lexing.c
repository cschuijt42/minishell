/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexing.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 19:43:04 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/02/16 19:43:04 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "h_colors.h"
#include "libft.h"
#include <stdbool.h>
#include <stdio.h>


int	pipe_or_redirect_token(char *input, int i, t_lexnode **token_list)
{
	if (input[i] == '|')
	{
		add_token_to_lexer_output(token_pipe, token_list);
		return (i + 1);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == input[i])
		{
			add_token_to_lexer_output(token_redirect_right_append, token_list);
			return (i + 2);
		}
		add_token_to_lexer_output(token_redirect_right, token_list);
		return (i + 1);
	}
	else
	{
		if (input[i + 1] == input[i])
		{
			add_token_to_lexer_output(token_wait_for_delimiter, token_list);
			return (i + 2);
		}
		add_token_to_lexer_output(token_redirect_left, token_list);
		return (i + 1);
	}
}
//funtion is fine but my brain goes nooo it can be cleaner

void	add_token_to_lexer_output(int token_type, t_lexnode **token_list)
{
	t_lexnode	*token;
	t_lexnode	*list_current;

	token = ft_calloc(sizeof(t_lexnode));
	if (!token)
		temp_error("malloc fail"); //will change
	token->token_type = token_type;
	if (!*token_list)
		*token_list = token;
	else
	{
		list_current = *token_list;
		while (list_current->next)
			list_current = list_current->next;
		list_current->next = token;
	}
}

int	read_quote_mode(char *str, char c, t_lexnode **token_list)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '$' && c == '"')
			insert_var();
	}

}

int	read_text_mode(char *str, int i, t_lexnode **token_list, int nested)
{
	int			start;
	t_lexnode	*new_node;

	start = i;
	new_node = ft_calloc(1, sizeof(t_lexnode));
	while (!is_text_mode_change(str[i]))
		i++;
	new_node->value = ft_substr(str, start, i - start);
	new_node->token_type = token_plain_text;
	if (nested)
		add_nested_node_to_lexer_output(new_node, token_list);
	else
		add_new_node_to_lexer_output(new_node, token_list);
	if (is_text_mode_change(str[i]) == 1)

	else if (is_text_mode_change(str[i] == 2))

	else

}

t_lexnode	*lexer(char *input)
{
	int			i;
	t_lexnode	*head;

	i = 0;
	head = NULL;
	while (input[i])
	{
		i += skip_whitespace(input);
		if (!input[i])
			break ;
		else if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			i = pipe_or_redirect_token(input, i, &head);
		else
			i = read_text_mode(input, i, &head, 0);
	}
	return (head);
}
