/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_exec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:47:59 by yzaim         #+#    #+#                 */
/*   Updated: 2023/06/26 13:48:42 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mem_alloc(t_var *mini)
{
	uint32_t	i;

	i = 0;
	mini->cmd_data->fd_in = 0;
	mini->cmd_data->fd_out = 1;
	mini->pid = ft_calloc(sizeof(pid_t), mini->n_cmd);
	if (!mini->pid)
		malloc_protect(mini);
	if (mini->n_cmd > 1)
	{
		mini->pipes = malloc(sizeof(int *) * (mini->n_cmd - 1));
		if (!mini->pipes)
			malloc_protect(mini);
		while (mini->pipes && i < mini->n_cmd - 1)
		{
			mini->pipes[i] = malloc(sizeof(int) * 2);
			if (!mini->pipes[i])
				malloc_protect(mini);
			i++;
		}
	}
}

void	ft_free_exec_alloc(t_var *mini)
{
	u_int32_t	i;

	i = 0;
	if (mini->pid)
		free(mini->pid);
	if (mini->n_cmd > 1)
	{
		while (mini->pipes && i < mini->n_cmd - 1)
		{
			free(mini->pipes[i]);
			i++;
		}
		free(mini->pipes);
	}
	mini->pid = NULL;
	mini->pipes = NULL;
}
