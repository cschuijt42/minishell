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
#include <stdbool.h>

void	temp_error(char *str)
{
	printf("%s %s \n", C_RED, str);
	exit(1);
}

static int	skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
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

bool	is_token(char c)
{
	static int	table[128] = \
	{
	['>'] = 1, ['<'] = 1, ['|'] = 1, \
	[' '] = 1, ['\''] = 1, ['"'] = 1
	};

	return (c <= 127 && c >= 0 && table[(int)c]);
}

t_lexnode	*lexer(char *input)
{
	t_lexnode	*head;
	t_lexnode	*node;

	input += skip_whitespace(input);
	head = NULL;
	while (*input)
	{
		if (is_token(*input))
		{
			head = token_checker(&input);
			break ;
		}
		input++;
	}
	if (!head)
		temp_error("no tokens found (or malloc error)");
	//eww doing it this way w double loops is ugly we can do better.. how tho?
	node = head;
	while (*input)
	{
		if (is_token(*input))
		{
			node->next = token_checker(&input);
			if (!node->next)
				temp_error("malloc fail");
			node = node->next;
		}
	}
	return (head);
}

t_lexnode	*token_checker(char *str, int *i)
{
	static t_lexnode	*(*table[128])(char **) = \
	{
	['>'] = NULL, ['<'] = NULL, ['|'] = NULL, \
	};
	char				*str_after;

	str_after = *str + 1;
	//(&(*str +1)) didnt work :s
	if (*str > 127 || *str < 0 || table[*str] == NULL)
		return (NULL);
	return ((*table[(int)*str])(&str_after));
}
