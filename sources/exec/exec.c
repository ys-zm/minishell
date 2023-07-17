/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:54:26 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/17 15:57:40 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_exec(t_var *mini)
{
	ft_init(mini);
	if (mini->n_cmd == 1)
		g_exit_code = single_cmd(mini);
	else
		g_exit_code = multiple_cmds(mini);
	if (g_exit_code == 137)
		malloc_protect(mini);
	else if (remove_here_docs(mini->here_doc_path) == false)
		malloc_protect(mini);
	ft_free_cmd_arr(mini->cmd_data, mini->n_cmd);
	mini->cmd_data = NULL;
	mini->n_cmd = 0;
}
