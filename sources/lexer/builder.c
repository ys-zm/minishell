/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builder.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 00:26:11 by fra           #+#    #+#                 */
/*   Updated: 2023/07/18 22:58:12 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	init_null(t_cmd *cmd, t_list *tokens)
{
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->cmd_name = NULL;
	cmd->full_cmd = NULL;
	cmd->n_words = count_words(tokens);
	cmd->n_redirect = count_redirections(tokens);
	cmd->redirections = NULL;
	cmd->files = NULL;
}

t_cmd_status	\
	build_cmd(t_cmd *cmd, char *curr_cmd, uint32_t order_cmd, char *hd_path)
{
	t_list			*tokens;
	t_cmd_status	status;

	status = CMD_OK;
	if (ft_is_empty_str(curr_cmd) == true)
		return (CMD_OK);
	tokens = tokenize(curr_cmd);
	if (tokens == NULL)
		return (CMD_MEM_ERR);
	init_null(cmd, tokens);
	if (cmd->n_words)
		status = fill_words(cmd, tokens);
	if ((status == CMD_OK) && cmd->n_redirect)
	{
		status = get_redirections(cmd, tokens, order_cmd, hd_path);
		if (status == CMD_OK)
			status = get_files(cmd, tokens);
	}
	ft_lstclear(&tokens, ft_free);
	return (status);
}
