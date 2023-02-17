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

"lexing.h"

t_lexnode	lexer(char *input)
{
	int	i;
	int	token_start;

	i = skip_whitespace(input);
	token_start = 0;
	while(input[i])
	{
		if(token_found(&input[i]))

	}
}
