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

# include "libft.h"
# include <errno.h>
# include "h_colors.h"

extern int	g_return_value;

typedef enum tokentypes
{
	token_redirect_left,
	token_heredoc,
	token_redirect_right,
	token_redirect_append,
	token_pipe,
	token_flag,
	token_plain_text
}	t_token;

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
	int					heredoc_pipe[2];
	int					pipe_out[2];
	pid_t				pid;
	struct s_command	*next;
	struct s_command	*prev;
	char				**arg_array;
}	t_command;

typedef struct s_argument {
	char				*content;
	struct s_argument	*next;
}	t_argument;

typedef struct s_redirect {
	char				*target;
	int					type;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_env_list
{
	struct s_env_list	*next;
	char				*key;
	char				*value;
}	t_env_list;

typedef struct s_shell
{
	t_env_list	*environment;
	t_lexnode	*lexer_output;
	t_command	*command_tree;
	char		**envp;
	char		**split_path;
}	t_shell;

# define SHELL_PROMPT "\x1b[38;2;0;255;0mFROGGYSHELL\x1b[0m: "

//  ----------------- enviroment ----------------

t_env_list	*parse_envp(char **envp);
char		*get_env_var_value(char *key, t_env_list *list);
char		**env_list_to_arr(t_env_list *list);
void		add_list_node_from_env_variable(char *env_line, t_env_list **list);
void		setup_all_heredocs(t_shell *shell);
void		add_env_node_to_list(t_env_list **list, char *key, char *value);

// ----------------- utils ----------------

void		clean_up_execution(t_shell *shell);
void		regenerate_path_array(t_shell *shell);

// --------------------------------- builtins --------------------------------

void		pwd(char **args, t_shell *shell);
void		cd(char **path, t_shell *shell);
void		echo(char **text, t_shell *shell);
void		export(char **env_line, t_shell *shell);
void		env(char **hoi, t_shell *shell);
void		builtin_exit(char **code, t_shell *shell);

// --------------------------------- temp --------------------------------

void		executor(t_shell *shell);

#endif
