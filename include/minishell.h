/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 17:21:34 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/03/06 17:21:34 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"

typedef struct s_env_list
{
	char			*key;
	char			*value;
	struct s_env_list	*next;
}	t_envir_var;
#endif
