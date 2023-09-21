/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_process.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:41:41 by yzaim         #+#    #+#                 */
/*   Updated: 2023/09/21 12:16:41 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_exit_code(t_var *mini)
{
	if (errno == 13)
		mini->status = 126;
	else
		mini->status = 127;
}

// Execution of single command using execve(). 
// Global variable g_exit_code is set to 0. 
// If it fails, g_exit_code is switched to 127 with ft_error_msg() function.
int	ft_exec_child_single(t_var *mini)
{
	char	*cmd_path;
	t_cmd	cmd;

	ft_do_redirections(mini, 0);
	cmd_path = NULL;
	cmd = mini->cmd_data[0];
	if (!cmd.cmd_name)
		exit(EXIT_SUCCESS);
	cmd_path = access_cmd_path(mini, cmd.cmd_name);
	mini->status = 0;
	execve(cmd_path, cmd.full_cmd, mini->env_arr);
	printf("execve fails\n");
	ft_exit_code(mini);
	ft_error_msg(cmd_path);
	ft_free_all(mini);
	exit(mini->status);
}

void	ft_call_execve(t_var *mini, t_cmd cmd)
{
	char	*cmd_path;

	cmd_path = access_cmd_path(mini, cmd.cmd_name);
	mini->status = 0;
	execve(cmd_path, cmd.full_cmd, mini->env_arr);
	free(cmd_path);
	ft_exit_code(mini);
	ft_error_msg(cmd_path);
}

int	ft_exec_child_multiple(t_var *mini, int index)
{
	t_cmd	cmd;

	cmd = mini->cmd_data[index];
	if (!cmd.cmd_name)
		exit(EXIT_SUCCESS);
	if (!ft_if_builtin(cmd.cmd_name))
		ft_call_execve(mini, cmd);
	else
		mini->status = ft_exec_builtin(mini, index, STDOUT_FILENO);
	exit(mini->status);
}

void	ft_exec_multiple(t_var *mini, u_int32_t index, int fd_in)
{
	if (mini->cmd_data[index].if_next)
		close(mini->pipe[READ]);
	if (fd_in != -1)
		mini->cmd_data[index].fd_in = fd_in;
	mini->cmd_data[index].fd_out = mini->pipe[WRITE];
	if (!mini->cmd_data[index].if_next)
		mini->cmd_data[index].fd_out = STDOUT_FILENO;
	if (ft_if_redir(mini, index))
		ft_file_redirect(mini, index);
	if (redirect_pipe_in(mini, index) == -1)
		exit(mini->status);
	if (redirect_pipe_out(mini, index) == -1)
		exit(mini->status);
	ft_exec_child_multiple(mini, index);
}
