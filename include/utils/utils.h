/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:12:06 by fra           #+#    #+#                 */
/*   Updated: 2023/07/01 02:19:18 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell/minishell.h"

// utils.c
void	move_chars(char *dest, char *src);

char	*remove_quotes(char *to_clear, bool free_string);

bool	is_quote(char to_check);

bool	is_arrow(char to_check);

char	*create_file_name(const char *fix_part, int32_t cnt);

#endif
