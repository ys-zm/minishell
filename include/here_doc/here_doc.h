/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:23:12 by fra           #+#    #+#                 */
/*   Updated: 2023/07/01 02:26:09 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H
# include "minishell/minishell.h"

// here_doc_handle.c
int32_t			find_next_eof_pos(char *cmd, uint32_t start_pos);

char			*isolate_eof(char *start);

uint32_t		get_order_cmd(char *str, uint32_t pos);

t_cmd_status	handle_here_doc(char *cmd, uint32_t *cnt, t_env *vars);

// here-doc_write.c
t_cmd_status	eof_here_doc(char **here_doc, t_cmd_status status);

t_cmd_status	aquire_input_hd(char *eof, char **here_doc);

int32_t			open_and_expand(bool exp, int32_t cnt, char **hd, t_env *vars);

t_cmd_status	write_here_doc(int cnt, char *del, bool exp_vars, t_env *vars);

t_cmd_status	fork_here_doc(int cnt, char *del, bool exp_vars, t_env *vars);

#endif
