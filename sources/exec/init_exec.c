/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_exec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:47:59 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/17 15:29:24 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_init(t_var *mini)
{
	uint32_t	i;

	i = 0;
	mini->cmd_data->fd_in = 0;
	mini->cmd_data->fd_out = 1;
	mini->f_pid = 0;
	while (i < mini->n_cmd)
	{
		if (i == mini->n_cmd - 1)
			mini->cmd_data[i].if_next = false;
		else
			mini->cmd_data[i].if_next = true;
		i++;
	}
}
