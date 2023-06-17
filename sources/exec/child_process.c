#include "minishell.h"


int ft_exec_child_single(t_var *mini, int index, int fd_out)
{
    char    *cmd_path;
    t_cmd   cmd;
    int     status_check;
    
    cmd_path = NULL;
    cmd = mini->cmd_data[index];
    if (!cmd.cmd_name)
        exit(EXIT_SUCCESS);
    if (!ft_if_builtin(cmd.cmd_name))
    {
        cmd_path = access_cmd_path(mini, cmd.cmd_name);
        g_exit_code = 0;
        // printf("path is: %s\n", cmd_path);
        execve(cmd_path, cmd.full_cmd, mini->env_arr);
        printf("execve value> %d\n", execve(cmd_path, cmd.full_cmd, mini->env_arr));
        free(cmd_path);
    }
    else
    {
        status_check = ft_exec_builtin(mini, index, fd_out);
        if (status_check == -1)
            mini->status = -1;
        exit(mini->status);
    }
    int pid = getpid();
    if (waitpid(pid, &mini->status, -1) < 0)
        return (-1);
    ft_error_msg(mini, cmd.cmd_name, 127);
    g_exit_code = 127;
    return mini->status;
    // exit(mini->status);
}


void ft_exec_child_multiple(t_var *mini, uint32_t index)
{
    if (index > 0)
        dup2(mini->pipes[index - 1][READ], STDIN_FILENO);
    if (index < mini->n_cmd - 1)
        dup2(mini->pipes[index][WRITE], STDOUT_FILENO);
    if (ft_if_redir(mini, index))
        ft_redirect(mini, index);
    close_pipes(mini);
    ft_exec_child_single(mini, index, STDOUT_FILENO);
}
