#include "minishell.h"

//how do the processes work if it is a sinlge command? don't you have to create a child process?
//how should I deal with builtin vs execve cmds?
int   single_cmd(t_var *mini)
{
    t_cmd   *cmd;
    int     exit_status;

    cmd = mini->cmd_data;
    if (!cmd->cmd_name)
    {
        ft_redir_type(mini, 0);
        return (0);
    }
    if (ft_if_builtin(cmd->cmd_name))
    {
        ft_redir_type(mini, 0);
        return (ft_exec_builtin(mini, 0, mini->cmd_data[0].fd_out));
    }
    if (ft_if_redir(mini, 0))
        ft_redirect(mini, 0);
    (mini)->pid[0] = fork();
    if ((mini)->pid[0] < 0)
        return (ft_error_msg(mini, "Fork failed.", 1), mini->status = -1, -1);
    if (mini->pid[0] == 0)
        ft_exec_child_single(mini, 0, STDOUT_FILENO);
    waitpid(mini->pid[0], &exit_status, 0);
    if (WIFEXITED(exit_status))
        return (WEXITSTATUS(exit_status));
    return (mini->status = -1, mini->status);
}

int multiple_cmds(t_var *mini)
{
    create_pipes(mini);
    process_management(mini);
    close_pipes(mini);
    return (wait_for_children(mini));
}

int    ft_exec(t_var *mini)
{
    ft_mem_alloc(mini);
    if (mini->n_cmd == 1)
        mini->status = single_cmd(mini);
    else
        mini->status = multiple_cmds(mini);
    return (mini->status);
    printf("exit code: %d\n", mini->status);
}