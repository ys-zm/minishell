/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:54:26 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/18 22:50:30 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_exec(t_var *mini)
{
	ft_init(mini);
	if (mini->n_cmd == 1)
		mini->status = single_cmd(mini);
	else
		mini->status = multiple_cmds(mini);
	if (mini->status == 137)
		malloc_protect(mini);
	else if (remove_here_docs(mini->hd_path) == false)
		malloc_protect(mini);
	ft_free_cmd_arr(mini);
	mini->cmd_data = NULL;
	mini->n_cmd = 0;
}
