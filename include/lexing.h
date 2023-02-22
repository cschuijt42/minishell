/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexing.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 19:43:14 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/02/16 19:43:14 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

typedef enum tokentypes
{
	redirect_right,
	redirect_right_append,
	redirect_left,
	wait_for_delimiter,
	buis, //dutch 4 pipe :)
	command,
	flag,
	plain_text
}		t_token;

typedef struct lexnode
{
	t_token			token_type;
	char			*value;
	struct lexnode	*next;
}	t_lexnode;

t_lexnode	*lexer(char *input);
void	temp_error(char *str);

#endif