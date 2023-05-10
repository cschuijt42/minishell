/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 15:44:22 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/03/20 15:44:22 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

typedef int	(*t_builtin_ptr)(t_argument *, t_shell *);

void	clean_up_heredocs(t_command *command);
void	setup_arg_array(t_command *command);

void	setup_child_process(t_shell *shell, t_command *command);

void	setup_command_redirects(t_command *command);

void	setup_input_redirect(t_redirect *redirect);
void	setup_output_redirect(t_redirect *redirect);
void	setup_heredoc_redirect(t_command *command);

bool	single_builtin_executor(t_command *cmd, t_shell *shell);
void	exec_if_builtin(t_command *cmd, t_shell *shell);

int		find_builtin_index(char *cmd);
void	backup_stdin_out(int *temp_inout);
void	restore_stdin_out(int *temp_std_fd);

#endif
