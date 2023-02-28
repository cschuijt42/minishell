/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/26 22:43:08 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/02/26 22:43:08 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_redirect_types {
	redirect_input,
	redirect_heredoc,
	redirect_output,
	redirect_output_append
}	t_redirect_types;

typedef struct s_command {
	char				*target;
	char				*target_expanded;
	struct s_argument	*arguments;
	struct s_redirect	*redirects;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_argument {
	char				*content;
	struct s_argument	*next;
}	t_argument;

typedef struct s_redirect {
	char				*target;
	char				*target_expanded;
	int					type;
	struct s_redirect	*next;
}	t_redirect;

t_command	*build_command_tree(t_lexnode *input);

#endif
