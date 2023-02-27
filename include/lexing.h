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
	token_redirect_right,
	token_redirect_right_append,
	token_redirect_left,
	token_wait_for_delimiter,
	token_pipe, //dutch 4 pipe :)
	token_flag,
	token_plain_text
}		t_token;


typedef struct lexnode
{
	t_token			token_type;
	char			*value;
	struct lexnode	*next;
}	t_lexnode;

typedef union frog
{
	int	nbr;
	char *swag;
}	t_frog;
t_lexnode	*lexer(char *input);
void		temp_error(char *str);

#endif