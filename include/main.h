/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 20:18:09 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/02/28 20:18:09 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAIN_H
# define MAIN_H

extern int	g_return_value;

typedef enum tokentypes
{
	token_redirect_left,
	token_heredoc,
	token_redirect_right,
	token_redirect_append,
	token_pipe,
	token_flag,
	token_plain_text,
	token_unquoted_var,
	token_quoted_var
}		t_token;

typedef struct s_lexnode
{
	t_token				token_type;
	char				*value;
	struct s_lexnode	*next;
	struct s_lexnode	*tree_next;
}	t_lexnode;

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

# define SHELL_PROMPT "\x1b[38;2;0;255;0mFROGGYSHELL:\x1b[0m "

#endif
