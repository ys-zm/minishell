/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiple_cmds.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:00:26 by yzaim         #+#    #+#                 */
/*   Updated: 2023/06/26 14:03:10 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_var *mini)
{
	u_int32_t	i;

	i = 0;
	while (i < mini->n_cmd - 1)
	{
		if (pipe(mini->pipes[i]) == -1)
		{
			ft_free_all(mini);
			ft_error_msg(mini, "Creating pipes failed", 1);
		}
		i++;
	}
}

void	close_pipes(t_var *mini)
{
	u_int32_t	i;

	i = 0;
	while (i < mini->n_cmd - 1)
	{
		close(mini->pipes[i][READ]);
		close(mini->pipes[i][WRITE]);
		i++;
	}
}

int	wait_for_children(t_var *mini)
{
	u_int32_t	i;
	int			exit_status;

	i = 0;
	while (i < mini->n_cmd)
	{
		waitpid(mini->pid[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			mini->status = WEXITSTATUS(exit_status);
		i++;
	}
	return (mini->status);
}

int	process_management(t_var *mini)
{
	u_int32_t	i;

	i = 0;
	while (i < mini->n_cmd)
	{
		mini->pid[i] = fork();
		if (mini->pid[i] == 0)
			ft_exec_multiple(mini, i);
		i++;
	}
	return (EXIT_SUCCESS);
}
