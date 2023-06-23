#include "minishell.h"

//how do the processes work if it is a sinlge command? don't you have to create a child process?
//how should I deal with builtin vs execve cmds?
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
		return (ft_error_msg(mini, "Fork failed.", 1), mini->status = -1, -1);
	if (mini->pid[0] == 0)
	{
		if (ft_if_redir(mini, 0))
		{
			if (ft_redirect(mini, 0))
				{
					ft_free_all(mini);
					exit(EXIT_FAILURE);
				}
		}
		ft_exec_child_single(mini);
	}
	waitpid(mini->pid[0], &exit_status, 0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);   
}

int	multiple_cmds(t_var *mini)
{
	create_pipes(mini);
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
}

