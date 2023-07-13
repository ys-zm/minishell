/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:54:26 by yzaim         #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/07/13 17:53:45 by yzaim         ########   odam.nl         */
=======
/*   Updated: 2023/07/13 16:33:26 by faru          ########   odam.nl         */
>>>>>>> c37ca1b273fda4dc3b7fea0b7fcd5484191fb738
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_do_redirections(t_var *mini, int index)
{
	if (ft_if_redir(mini, index))
	{
		if (ft_file_redirect(mini, index))
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
<<<<<<< HEAD
	init_sig_handle(1);
	(mini)->f_pid = fork();
	if ((mini)->f_pid < 0)
		return (ft_error_msg("Fork failed"), 1);
	if (mini->f_pid == 0)
=======
	(mini)->pid[0] = fork();
	if ((mini)->pid[0] < 0)
		return (ft_error_msg(mini, "Fork failed", 1), 1);
	if (mini->pid[0] == 0)
>>>>>>> c37ca1b273fda4dc3b7fea0b7fcd5484191fb738
	{
		init_sig_handle(2);
		ft_do_redirections(mini, 0);
		ft_exec_child_single(mini);
	}
<<<<<<< HEAD
	waitpid(mini->f_pid, &exit_status, 0);
=======
	init_sig_handle(1);
	waitpid(mini->pid[0], &exit_status, 0);
>>>>>>> c37ca1b273fda4dc3b7fea0b7fcd5484191fb738
	init_sig_handle(0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
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
	{
		close(mini->pipe[READ]);
		close(mini->pipe[WRITE]);
		return (ft_error_msg("fork"), -1);
	}
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


int	multiple_cmds(t_var *mini)
{
	int			exit_status;
	int			status = 0;

	mini->f_pid = pipe_and_fork(mini, -1, 0);
	if (mini->f_pid == -1)
		return (1);
	waitpid(mini->f_pid, &exit_status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(exit_status))
		status = WEXITSTATUS(exit_status);
	return (status);
}

// static void	dup_fds(int fd_in, int fd_out)
// {
// 	dup2(fd_in, STDIN_FILENO);
// 	dup2(fd_out, STDOUT_FILENO);
// }

void	ft_exec(t_var *mini)
{
	// int fd_in = dup(STDIN_FILENO);
	// int fd_out = dup(STDOUT_FILENO);
	ft_mem_alloc(mini);
	if (mini->n_cmd == 1)
		g_exit_code = single_cmd(mini);
	else
		g_exit_code = multiple_cmds(mini);
	if (g_exit_code == 137)
		malloc_protect(mini);
	else if (remove_here_docs(mini->here_doc_path) == false)
		malloc_protect(mini);
	ft_free_cmd_arr(mini->cmd_data, mini->n_cmd);
	ft_free_exec_alloc(mini);
	mini->cmd_data = NULL;
	mini->n_cmd = 0;
	// dup_fds(fd_in, fd_out);
	// close(fd_in);
	// close(fd_out);
}
