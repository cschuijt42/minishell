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
# include <limits.h>
# include <stdio.h>

extern int	g_interrupted;

typedef enum e_error_types
{
	error_continue,
	error_unclosed_quote,
	error_loose_pipe,
	error_loose_redirect_token,
	error_empty_command_node,
	error_cant_access_infile,
	error_cant_open_infile,
	error_cant_access_outfile,
	error_cant_dup_fd
}	t_error_types;

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
	t_env_list	*env_list;
	t_lexnode	*lexer_output;
	t_command	*command_tree;
	char		*cwd;
	char		**envp;
	char		**split_path;
	int			return_value;
	int			error_value;
}	t_shell;

# define SHELL_PROMPT "\x1b[38;2;0;255;0mFROGGYSHELL\x1b[0m: "

//  ----------------- enviroment ----------------

t_env_list	*parse_envp(char **envp);
char		*get_env_var_value(char *key, t_env_list *list);
char		**env_list_to_arr(t_env_list *list);
void		add_env_var(char *key, char *value, t_shell *shell);
t_env_list	*find_env_var(char *key, t_shell *shell);
t_env_list	*env_line_to_node(char *env_line);
void		free_node(t_env_list *node);
void		remove_node_and_remake_env(t_env_list *remove_me, t_shell *shell);
void		regenerate_env_array(t_shell *shell);
void		update_shell_level(t_shell *shell);

// ----------------- utils ----------------

void		clean_up_execution(t_shell *shell);
void		regenerate_path_array(t_shell *shell);
t_env_list	*find_env_var(char *key, t_shell *shell);

// --------------------------------- builtins --------------------------------

int			pwd(t_argument *args, t_shell *shell);
int			cd(t_argument *args, t_shell *shell);
int			echo(t_argument *args, t_shell *shell);
int			export(t_argument *args, t_shell *shell);
int			env(t_argument *args, t_shell *shell);
int			builtin_exit(t_argument *args, t_shell *shell);
int			unset(t_argument *args, t_shell *shell);

void		print_2d_array_alphabetically(char **envp);

// --------------------------------- execution --------------------------------

void		executor(t_shell *shell);
void		setup_all_heredocs(t_shell *shell);

// --------------------------------- signals --------------------------------

void		sigint_handler_generic(int signum);
void		sigint_handler_interactive(int signum);
void		sigint_handler_heredoc(int signum);

// ----------------------------- error handling -----------------------------

void		print_error_value(int error_value);
void		print_error_message_exit(char *message, int return_value);
int			print_error_message_return(char *message, int return_value);
int			print_error_message_perror(char *message, int return_value);

// --------------------------------- cleanup --------------------------------

int			clean_up_shell_struct(t_shell *shell);
void		clean_up_lexer_output(t_shell *shell);
void		clean_up_command_tree(t_shell *shell);
void		clean_up_env_list(t_shell *shell);

#endif
