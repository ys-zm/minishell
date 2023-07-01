/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 01:37:15 by fra           #+#    #+#                 */
/*   Updated: 2023/07/01 02:06:03 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell/minishell.h"

//tokenizer.c
int32_t	    isolate_word(char *input, char **new_word);

bool		is_redirection(t_list *token);

t_red_type	get_type_redirection(char *to_check);

t_list		*tokenize(char *input);

// lexer.c
uint32_t	count_words(t_list *tokens);

char		**fill_words(t_list *tokens);

uint32_t	count_redirections(t_list *tokens);

t_red_type	*get_redirections(t_list *tokens, uint32_t n_redirect, int order);

char		**get_files(t_list *tokens, uint32_t n_redirect);

//builder.c
bool	    set_cmd(t_list *tokens, t_cmd *cmd);

bool	    set_reds(t_list *tokens, t_cmd *cmd, uint32_t order);

t_cmd	    *build_cmd(t_cmd *cmd, char *curr_cmd, uint32_t order_cmd);

#endif
