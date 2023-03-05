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

int	pipe_or_redirect_token(char *input, int i, t_lexnode **token_list)
{
	if (input[i] == '|')
	{
		add_node_to_lexer_output(NULL, token_pipe, token_list);
		return (i + 1);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == input[i])
		{
			add_node_to_lexer_output(NULL, token_redirect_append, token_list);
			return (i + 2);
		}
		add_node_to_lexer_output(NULL, token_redirect_right, token_list);
		return (i + 1);
	}
	else
	{
		if (input[i + 1] == input[i])
		{
			add_node_to_lexer_output(NULL, token_heredoc, token_list);
			return (i + 2);
		}
		add_node_to_lexer_output(NULL, token_redirect_left, token_list);
		return (i + 1);
	}
}

int	read_text_mode(char *str, int i, t_lexnode **token_list, int nested)
{
	int		start;
	char	*text;

	start = i;
	while (!is_text_mode_change(str[i]))
		i++;
	text = ft_substr(str, start, i - start);
	if (nested)
		add_nested_node_to_lexer_output(text, token_plain_text, token_list);
	else
		add_node_to_lexer_output(text, token_plain_text, token_list);
	if (is_text_mode_change(str[i]) == 1)
		return (i);
	else if (is_text_mode_change(str[i] == 2))
		return (read_quote_mode(str, str[i], i + 1, token_list));
	else if (!ft_isalnum(str[i + 1]) && str[i + 1] != '_' && str[i + 1] != '?')
	{
		add_nested_node_to_lexer_output(ft_strdup("$"), \
										token_plain_text, token_list);
		return (read_text_mode(str, i + 1, token_list, 1));
	}
	else
		return (read_var_mode(str, i + 1, token_list, 0));
}

int	read_quote_mode(char *str, char c, int i, t_lexnode **token_list)
{
	int		start;
	char	*text;

	start = i;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '$' || str[i] == c)
			break ;
		i++;
	}
	if (str[i] == '\0')
		temp_error("Unclosed quote in input");
	text = ft_substr(str, start, i - start);
	add_nested_node_to_lexer_output(text, token_plain_text, token_list);
	if (c == '$')
		return (read_var_mode(str, i + 1, token_list, 1));
	else
		return (read_text_mode(str, i + 1, token_list, 1));
}

int	read_var_mode(char *str, int i, t_lexnode **token_list, int in_quotes)
{
	char		*var_name;
	int			start;

	start = i;
	if (str[i] == '?')
	{
		i++;
		var_name = ft_strdup("?");
	}
	else
	{
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		var_name = ft_substr(str, start, i - start);
	}
	if (in_quotes)
	{
		add_nested_node_to_lexer_output(var_name, token_quoted_var, token_list);
		return (read_quote_mode(str, '"', i, token_list));
	}
	add_nested_node_to_lexer_output(var_name, token_unquoted_var, token_list);
	return (read_text_mode(str, i, token_list, 1));
}

t_lexnode	*lexer(char *input)
{
	int			i;
	t_lexnode	*head;

	i = 0;
	head = NULL;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		else if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			i = pipe_or_redirect_token(input, i, &head);
		else
			i = read_text_mode(input, i, &head, 0);
	}
	return (head);
}
