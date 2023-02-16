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

typedef struct lexnode
{
	int		token_type;
	char	*value;
	lexnode	*next;
	lexnode	*prev;
}	t_lexnode;