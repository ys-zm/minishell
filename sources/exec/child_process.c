#include "minishell.h"

// Execution of single command using execve(). Global variable g_exit_code is set to 0. 
// If it fails, g_exit_code is switched to 127 with ft_error_msg() function.
int	ft_exec_child_single(t_var *mini)
{
	char	*cmd_path;
	t_cmd	cmd;

	cmd_path = NULL;
	cmd = mini->cmd_data[0];
	if (!cmd.cmd_name)
		exit(EXIT_SUCCESS);
	cmd_path = access_cmd_path(mini, cmd.cmd_name);
	g_exit_code = 0;
	mini->env_arr = ft_list_to_arr(mini, *(mini->env_list));
	execve(cmd_path, cmd.full_cmd, mini->env_arr);
	free(cmd_path);
	ft_error_msg(mini, cmd.cmd_name, 127);
	ft_free_all(mini);	
	exit(g_exit_code); //not sure if I should exit here
}

int	ft_exec_child_multiple(t_var *mini, int index, int fd_out)
{
	char    *cmd_path;
	t_cmd   cmd;
	int	status_check;

	status_check = 0;
	cmd_path = NULL;
	cmd = mini->cmd_data[index];
	if (!cmd.cmd_name)
		exit(EXIT_SUCCESS);
	if (!ft_if_builtin(cmd.cmd_name))
	{
		cmd_path = access_cmd_path(mini, cmd.cmd_name);
		g_exit_code = 0;
		execve(cmd_path, cmd.full_cmd, mini->env_arr);
		free(cmd_path);
		g_exit_code = 127;
	}
	else
	{	
		g_exit_code = 0;
		status_check = ft_exec_builtin(mini, index, fd_out);
		if (status_check)
			g_exit_code = status_check;
	}
	ft_error_msg(mini, cmd.cmd_name, g_exit_code);
	ft_free_all(mini);
	exit(g_exit_code);
}


void ft_exec_multiple(t_var *mini, u_int32_t index)
{
    if (index > 0)
        dup2(mini->pipes[index - 1][READ], STDIN_FILENO);
    if (index < mini->n_cmd - 1)
        dup2(mini->pipes[index][WRITE], STDOUT_FILENO);
    if (ft_if_redir(mini, index))
        ft_redirect(mini, index);
    close_pipes(mini);
    ft_exec_child_multiple(mini, index, STDOUT_FILENO);
}
