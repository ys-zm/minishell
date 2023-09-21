/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:23:12 by fra           #+#    #+#                 */
/*   Updated: 2023/09/21 13:00:06 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H
# include "minishell/minishell.h"

// here_doc_handle.c
int32_t			find_next_eof_pos(char *cmd, uint32_t start_pos);

char			*isolate_del(char *start);

uint32_t		get_order_cmd(char *str, uint32_t pos);

t_cmd_status	handle_here_doc(char *cmd, uint32_t *cnt, t_var *mini);

bool			remove_here_docs(char *hd_path);

// here_doc_write.c
t_cmd_status	del_here_doc(char **here_doc, t_cmd_status status);

t_cmd_status	aquire_input_hd(char *eof, char **here_doc);

int32_t			open_and_expand(char **hd, int32_t cnt, bool exp, t_var *mini);

void			write_here_doc(int cnt, char *del, t_var *mini);

t_cmd_status	fork_here_doc(int cnt, char *del, t_var *mini);

#endif
