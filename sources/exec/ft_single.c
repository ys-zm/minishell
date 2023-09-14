/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_single.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:54:26 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/17 12:56:35 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

int	single_cmd(t_var *mini)
{
	t_cmd	*cmd;
	int		exit_status;

	cmd = mini->cmd_data;
	if (!cmd->cmd_name)
		return (ft_redir_type(mini, 0), EXIT_SUCCESS);
	if (ft_if_builtin(cmd->cmd_name))
		return (ft_run_builtin(mini));
	init_sig_handle(1);
	(mini)->f_pid = fork();
	if ((mini)->f_pid < 0)
		return (ft_error_msg("Fork failed"), 1);
	if (mini->f_pid == 0)
	{
		init_sig_handle(2);
		ft_exec_child_single(mini);
	}
	waitpid(mini->f_pid, &exit_status, 0);
	init_sig_handle(0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGINT)
			return (130);
		if (WTERMSIG(exit_status) == SIGQUIT)
			return (131);
	}
	return (EXIT_FAILURE);
}
