/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:03:25 by fra           #+#    #+#                 */
/*   Updated: 2023/07/01 02:05:59 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "minishell/minishell.h"

// check_char.c
bool    is_valid_symbol(char *string, uint32_t pos_to_check, char check);

bool    is_valid_space(char *string, uint32_t pos_to_check);

bool    is_valid_arrow(char *string, uint32_t pos_to_check);

bool    is_valid_dollar(char *string, uint32_t pos_to_check);

bool    is_valid_quote(char *string, uint32_t pos_to_check);

// check_sintax.c
bool    check_quotes(char *cmd);

bool    check_pipes(char *cmd);

bool    check_redirections(char *str);

bool    check_sintax(char *cmd);

// check_string.c
bool    is_empty(char *to_check);

bool    has_trailing_pipe(char	*cmd);

bool	is_outside_quotes(char *string, uint32_t pos_to_check);

#endif
