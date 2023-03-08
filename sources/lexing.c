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

int	pipe_or_redirect_token(char *input, int i, t_shell *shell)
{
	if (input[i] == '|')
	{
		add_node_to_lexer_output(NULL, token_pipe, shell);
		return (i + 1);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == input[i])
		{
			add_node_to_lexer_output(NULL, token_redirect_append, shell);
			return (i + 2);
		}
		add_node_to_lexer_output(NULL, token_redirect_right, shell);
		return (i + 1);
	}
	else
	{
		if (input[i + 1] == input[i])
		{
			add_node_to_lexer_output(NULL, token_heredoc, shell);
			return (i + 2);
		}
		add_node_to_lexer_output(NULL, token_redirect_left, shell);
		return (i + 1);
	}
}

int	read_text_mode(char *str, int i, t_shell *shell, int nested)
{
	int		start;
	char	*text;

	start = i;
	while (!is_text_mode_change(str[i]))
		i++;
	text = ft_substr(str, start, i - start);
	if (nested)
		add_nested_node_to_lexer_output(text, token_plain_text, shell);
	else
		add_node_to_lexer_output(text, token_plain_text, shell);
	if (is_text_mode_change(str[i]) == 1)
		return (i);
	else if (is_text_mode_change(str[i]) == 2)
		return (read_quote_mode(str, str[i], i + 1, shell));
	else if (!ft_isalnum(str[i + 1]) && str[i + 1] != '_' && str[i + 1] != '?')
	{
		add_nested_node_to_lexer_output(ft_strdup("$"), \
										token_plain_text, shell);
		return (read_text_mode(str, i + 1, shell, 1));
	}
	else
		return (read_var_mode(str, i + 1, shell, 0));
}

int	read_quote_mode(char *str, char closing_quote, int i, t_shell *shell)
{
	int		start;
	char	*text;

	start = i;
	while (str[i] && str[i] != closing_quote)
	{
		if (str[i] == closing_quote)
			break ;
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || \
								str[i + 1] == '_' || str[i + 1] == '?'))
			break ;
		i++;
	}
	if (str[i] == '\0')
		error_exit("Unclosed quote in input", 1);
	text = ft_substr(str, start, i - start);
	add_nested_node_to_lexer_output(text, token_plain_text, shell);
	if (str[i] == '$')
		return (read_var_mode(str, i + 1, shell, 1));
	else
		return (read_text_mode(str, i + 1, shell, 1));
}

int	read_var_mode(char *str, int i, t_shell *shell, int in_quotes)
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
		expand_variable_in_quotes(var_name, shell);
		return (read_quote_mode(str, '"', i, shell));
	}
	expand_variable(var_name, shell, 0);
	return (read_text_mode(str, i, shell, 1));
}

void	lexer(t_shell *shell, char *input)
{
	int	i;

	i = 0;
	shell->lexer_output = NULL;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		else if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			i = pipe_or_redirect_token(input, i, shell);
		else
			i = read_text_mode(input, i, shell, 0);
	}
	condense_lexer_output(&(shell->lexer_output));
}
