/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:54:26 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/12 22:19:03 by yzaim         ########   odam.nl         */
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
	init_sig_handle(1);
	(mini)->f_pid = fork();
	if ((mini)->f_pid < 0)
		return (ft_error_msg(mini, "Fork failed", 1), 1);
	if (mini->f_pid == 0)
	{
		init_sig_handle(2);
		ft_do_redirections(mini, 0);
		ft_exec_child_single(mini);
	}
	waitpid(mini->f_pid, &exit_status, 0);
	init_sig_handle(0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
}

// int	multiple_cmds(t_var *mini)
// {
// 	if (create_pipes(mini))
// 		return (EXIT_FAILURE);
// 	process_management(mini);
// 	close_pipes(mini);
// 	return (wait_for_children(mini));
// }

//in parent: only close write of current and read of previous
int	ft_parent_close_fds(t_var *mini, int fd_in, u_int32_t index)
{
	if (mini->cmd_data[index].if_next == true)
	{
		printf("parent close write: %d\n", mini->pipe[WRITE]);
		if (close(mini->pipe[WRITE]) == -1)
		{
			ft_write_error(2, "close", NULL, "write fd close failed");
			return (EXIT_FAILURE);
		}
	}
	printf("parent close read: %d\n", fd_in);
	if (fd_in > 0)
	{
		if (close(fd_in) == -1)
		{
			ft_write_error(2, "close", NULL, "prev read fd close failed");
			printf("for index: %u\n", index);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	pipe_and_fork(t_var *mini, int fd_prev, uint32_t index)
{
	pid_t	pid;

	if (mini->cmd_data[index].if_next == true && pipe(mini->pipe) == -1)
	{
		return (ft_error_msg(mini, "pipe", 1), 1);
	}
	init_sig_handle(1);
	pid = fork();
	if (pid == -1)
	{
		close(mini->pipe[READ]);
		close(mini->pipe[WRITE]);
		return (ft_error_msg(mini, "fork", 1), 1);
	}
	if (pid == 0)
	{
		printf("cmd: %s\n", mini->cmd_data[index].cmd_name);
		printf("read: %d\n", mini->pipe[READ]);
		printf("write: %d\n", mini->pipe[WRITE]);
		printf("fd_prev: %d\n", fd_prev);
		init_sig_handle(2);
		ft_exec_multiple(mini, index, fd_prev);
	}
	init_sig_handle(0);
	if (ft_parent_close_fds(mini, fd_prev, index))
		return (EXIT_FAILURE);
	if (index == mini->n_cmd - 1)
	{
		return (pid);
	}
	return (pipe_and_fork(mini, mini->pipe[READ], index + 1));
}

int	multiple_cmds(t_var *mini)
{
	uint32_t	i;
	int			exit_status;
	int			status = 0;

	i = 0;
	while (i < mini->n_cmd)
	{
		if (i != mini->n_cmd - 1)
			mini->cmd_data[i].if_next = true;
		i++;
	}
	
	mini->f_pid = pipe_and_fork(mini, STDIN_FILENO, 0);
	waitpid(mini->f_pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		status = WEXITSTATUS(exit_status);
	return (status);
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
