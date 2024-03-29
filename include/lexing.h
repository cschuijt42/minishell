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
# include "minishell.h"

void	lexer(t_shell *shell, char *input);

int		is_text_mode_change(char c);
int		skip_whitespace(char *str, int i);

void	add_node_to_lexer_output(char *content, int token_type, t_shell *shell);
void	add_nested_node_to_lexer_output(char *content, int token_type, \
										t_shell *shell);

int		pipe_or_redirect_token(char *input, int i, t_shell *shell);
int		read_quote_mode(char *str, char closing_quote, int i, t_shell *shell);
int		read_text_mode(char *str, int i, t_shell *shell, int nested);
int		read_var_mode(char *str, int i, t_shell *shell, int in_quotes);

void	expand_variable_in_quotes(char *var_name, t_shell *shell);
void	expand_variable(char *var_name, t_shell *shell, int i);

void	condense_lexer_output(t_lexnode **token_list);
void	condense_token(t_lexnode *token);

#endif
