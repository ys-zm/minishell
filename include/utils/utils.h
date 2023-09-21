/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:12:06 by fra           #+#    #+#                 */
/*   Updated: 2023/09/21 13:00:22 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell/minishell.h"

// utils.c
void	move_chars(char *dest, char *src);

char	*remove_quotes(char *to_clear, bool free_string);

char	*create_file_name(const char *fix_part, char *path_file, int32_t cnt);

bool	is_actual_file(char *file_name);

void	print_cmd(t_var	*mini);

#endif
