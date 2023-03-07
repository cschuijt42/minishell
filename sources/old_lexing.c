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


int	easy_node(char *input, int i, t_lexnode **token_list)
{
	if (input[i] == '|')
	{
		add_token(token_pipe, token_list);
		return (i + 1);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == input[i])
		{
			add_token(token_redirect_right_append, token_list);
			return (i + 2);
		}
		add_token(token_redirect_right, token_list);
		return (i + 1);
	}
	else
	{
		if (input[i + 1] == input[i])
		{
			add_token(token_wait_for_delimiter, token_list);
			return (i + 2);
		}
		add_token(token_redirect_left, token_list);
		return (i + 1);
	}
}
//funtion is fine but my brain goes nooo it can be cleaner

void	add_token(int token_type, t_lexnode **token_list)
{
	t_lexnode	*token;
	t_lexnode	*list_current;

	token = ft_calloc(sizeof(t_lexnode));
	if (!token)
		error_exit("malloc fail", errno); //will change
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

int	quote_mode(char *str, char c, t_lexnode **token_list)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '$' && c == '"')
			insert_var();
	}

}

int	text_reading(char *str, int i, t_lexnode **token_list)
{
	int		start_pos;

	start_pos = i;

	while (str[i] != is_delim(str[i]))
		i++;
	if (str[i] == '\'' || str[i] == '"')
		i = quote_mode(str, str[i + 1], token_list);

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
			i = easy_node(input, i, &head);
		else
			i = text_reading(input, i, &head);
	}
}
