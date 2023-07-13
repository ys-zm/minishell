/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:54:26 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/13 16:33:26 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_do_redirections(t_var *mini, int index)
{
	if (ft_if_redir(mini, index))
	{
		if (ft_redirect(mini, index))
		{
			ft_free_all(mini);
			exit(EXIT_FAILURE);
		}
	}
}

int	single_cmd(t_var *mini)
{
	t_cmd	*cmd;
	int		exit_status;

	cmd = mini->cmd_data;
	if (!cmd->cmd_name)
		return (ft_redir_type(mini, 0), EXIT_SUCCESS);
	if (ft_if_builtin(cmd->cmd_name))
	{
		if (ft_redir_type(mini, 0))
			return (EXIT_FAILURE);
		return (ft_exec_builtin(mini, 0, mini->cmd_data[0].fd_out));
	}
	(mini)->pid[0] = fork();
	if ((mini)->pid[0] < 0)
		return (ft_error_msg(mini, "Fork failed", 1), 1);
	if (mini->pid[0] == 0)
	{
		init_sig_handle(2);
		ft_do_redirections(mini, 0);
		ft_exec_child_single(mini);
	}
	init_sig_handle(1);
	waitpid(mini->pid[0], &exit_status, 0);
	init_sig_handle(0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
}

int	multiple_cmds(t_var *mini)
{
	if (create_pipes(mini))
		return (EXIT_FAILURE);
	process_management(mini);
	close_pipes(mini);
	return (wait_for_children(mini));
}

void	ft_exec(t_var *mini)
{
	ft_mem_alloc(mini);
	if (mini->n_cmd == 1)
		g_exit_code = single_cmd(mini);
	else
		g_exit_code = multiple_cmds(mini);
	if (g_exit_code == 137)
	{
		malloc_protect(mini);
	}
	else if (remove_here_docs(mini->here_doc_path) == false)
		malloc_protect(mini);
	ft_free_cmd_arr(mini->cmd_data, mini->n_cmd);
	ft_free_exec_alloc(mini);
	mini->cmd_data = NULL;
	mini->n_cmd = 0;
}
