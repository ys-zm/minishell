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
        global_exit_code = 0;
        execve(cmd_path, cmd.full_cmd, mini->env_arr);
        free(cmd_path);
    }
    else
    {
        status_check = ft_exec_builtin(&mini, index, fd_out);
        if (status_check == 0)
            exit (EXIT_SUCCESS);
        else if (status_check == -1 && mini->status == -1)
            exit(mini->status);
    }
    ft_error_msg(mini, "", 127);
    // child_error_handler();
    global_exit_code = 127;
    exit(mini->status);
}


void ft_exec_child_multiple(t_var *mini, u_int32_t index)
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