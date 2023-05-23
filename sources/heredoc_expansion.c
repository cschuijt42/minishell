/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expansion.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 12:31:54 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/23 12:31:54 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_and_free_substr(char **dest, char *src, int start, int len)
{
	char	*result;
	char	*substring;

	substring = ft_substr(src, start, len);
	if (!substring)
		exit(print_error_message_perror("malloc error", 1));
	result = ft_strjoin(*dest, substring);
	if (!result)
		exit(print_error_message_perror("malloc error", 1));
	free(substring);
	if (*dest)
		free(*dest);
	*dest = result;
}

int	expand_heredoc_partial(char *input, int position, char **current)
{
	int	count;

	count = 0;
	while (input[position + count] && input[position + count] != '$')
		count++;
	join_and_free_substr(current, input, position, count);
	return (position + count);
}

int	expand_return_value(char **current, t_shell *shell, int return_value)
{
	char	*var_value;

	var_value = ft_itoa(shell->return_value);
	if (!var_value)
		exit(print_error_message_perror("malloc failure", 1));
	join_and_free_substr(current, var_value, 0, ft_strlen(var_value));
	free(var_value);
	return (return_value);
}

int	expand_heredoc_variable(char *input, int position, \
								t_shell *shell, char **current)
{
	int		len;
	char	*var_name;
	char	*var_value;

	len = 0;
	position++;
	if (input[position] == '?')
		return (expand_return_value(current, shell, position + 1));
	if (!ft_isalpha(input[position]) && input[position] != '_')
	{
		join_and_free_substr(current, "$", 0, 1);
		return (position);
	}
	while (ft_isalnum(input[position + len]) || input[position + len] == '_')
		len++;
	var_name = ft_substr(input, position, len);
	if (!var_name)
		exit(print_error_message_perror("malloc error", 1));
	var_value = get_env_var_value(var_name, shell->env_list);
	if (var_value)
		join_and_free_substr(current, var_value, 0, ft_strlen(var_value));
	free(var_name);
	return (position + len);
}

void	expand_heredoc_variables(char **input, t_shell *shell)
{
	int		position;
	char	*expanded_str;

	if (!*input)
		return ;
	position = 0;
	expanded_str = NULL;
	while ((*input)[position])
	{
		if ((*input)[position] == '$')
			position = expand_heredoc_variable(*input, position, \
												shell, &expanded_str);
		else
			position = expand_heredoc_partial(*input, position, &expanded_str);
	}
	free(*input);
	*input = expanded_str;
}
