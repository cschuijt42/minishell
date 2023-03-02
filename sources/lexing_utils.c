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
#include <stdbool.h>

void	temp_error(char *str)
{
	printf("%s %s \n", C_RED, str);
	exit(1);
}

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

int	skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	return (i);
}

t_lexnode	*single_quotes(char **str)
{
	int			i;
	t_lexnode	*node;

	i = 0;
	while (*str[i] && *str[i] != '\'')
		i++;
	if (*str[i] != '\'')
		temp_error("missing closing quote!");
	node = malloc(sizeof(t_lexnode));
	if (!node)
		temp_error("malloc fail");
	node->token_type = token_plain_text;
	node->value = ft_substr(*str, 0, i);
	if (!node->value)
		temp_error("malloc fail");
	*str += i;
	return (node);
}
