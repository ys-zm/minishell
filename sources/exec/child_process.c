#include "minishell.h"


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
	printf("path is: %s\n", cmd_path);
	execve(cmd_path, cmd.full_cmd, mini->env_arr);
	printf("execve fails\n");
	free(cmd_path);
	ft_error_msg(mini, cmd.cmd_name, 127);
	g_exit_code = 127;
	exit(g_exit_code);
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
		printf("path is: %s\n", cmd_path);
		execve(cmd_path, cmd.full_cmd, mini->env_arr);
		printf("execve fails\n");
		free(cmd_path);
	}
	else
		status_check = ft_exec_builtin(mini, index, fd_out);
	ft_error_msg(mini, cmd.cmd_name, 127);
	if (status_check != 0)
		g_exit_code = status_check;
	else
		g_exit_code = 127;
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
