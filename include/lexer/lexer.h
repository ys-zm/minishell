/* ************************************************************************** */
/*		                                                                      */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 01:37:15 by fra           #+#    #+#                 */
/*   Updated: 2023/07/18 21:07:53 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell/minishell.h"

//tokenizer.c
int32_t			isolate_word(char *input, char **new_word);

bool			is_redirection(t_list *token);

t_red_type		get_type_redirection(char *to_check);

t_list			*tokenize(char *input);

// lexer.c
uint32_t		count_words(t_list *tokens);

t_cmd_status	fill_words(t_cmd *cmd, t_list *tokens);

uint32_t		count_redirections(t_list *tokens);

t_cmd_status	\
get_redirections(t_cmd *cmd, t_list *tokens, int order, char *hd);

t_cmd_status	get_files(t_cmd *cmd, t_list *tokens);

//builder.c
void			init_null(t_cmd *cmd, t_list *tokens);

t_cmd_status	\
build_cmd(t_cmd *cmd, char *curr_cmd, uint32_t order_cmd, char *hd_path);

#endif
