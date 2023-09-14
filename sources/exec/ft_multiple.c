/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_multiple.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:54:26 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/17 12:56:06 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_close_pipe(int *pipe)
{
	close(pipe[READ]);
	close(pipe[WRITE]);
}

int	pipe_and_fork(t_var *mini, int fd_prev, uint32_t index)
{
	pid_t	pid;

	if (mini->cmd_data[index].if_next == true)
	{
		if (pipe(mini->pipe) == -1)
			return (ft_error_msg("pipe"), -1);
	}
	init_sig_handle(1);
	pid = fork();
	if (pid == -1)
		return (ft_close_pipe(mini->pipe), ft_error_msg("fork"), -1);
	if (pid == 0)
	{
		init_sig_handle(2);
		ft_exec_multiple(mini, index, fd_prev);
	}
	init_sig_handle(0);
	if (ft_parent_close_fds(mini, fd_prev, index))
		return (EXIT_FAILURE);
	if (index == mini->n_cmd - 1)
		return (pid);
	return (pipe_and_fork(mini, mini->pipe[READ], index + 1));
}

//in parent: only close write of current and read of previous
int	ft_parent_close_fds(t_var *mini, int fd_in, u_int32_t index)
{
	if (mini->cmd_data[index].if_next == true)
	{
		if (close(mini->pipe[WRITE]) == -1)
		{
			ft_write_error(2, "close", NULL, "write fd close failed");
			return (EXIT_FAILURE);
		}
	}
	if (fd_in != -1)
	{
		if (close(fd_in) == -1)
		{
			ft_write_error(2, "close", NULL, "prev read fd close failed");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	multiple_cmds(t_var *mini)
{
	int	exit_status;
	int	status;

	status = 0;
	mini->f_pid = pipe_and_fork(mini, -1, 0);
	if (mini->f_pid == -1)
		return (1);
	waitpid(mini->f_pid, &exit_status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(exit_status))
		status = WEXITSTATUS(exit_status);
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGINT)
			return (130);
		if (WTERMSIG(exit_status) == SIGQUIT)
			return (131);
	}
	return (status);
}
