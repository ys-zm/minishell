#include "minishell.h"

bool ft_if_builtin(char *func)
{
    if (!ft_strcmp(func, "cd"))
        return (true);
    if (!ft_strcmp(func, "echo"))
        return (true);
    if (!ft_strcmp(func, "env"))
        return (true);
    if (!ft_strcmp(func, "exit"))
        return (true);
    if (!ft_strcmp(func, "export"))
        return (true);
    if (!ft_strcmp(func, "pwd"))
        return (true);
    if (!ft_strcmp(func, "unset"))
        return (true);
    return (false);
}

int    ft_exec_builtin(t_var *mini, int index, int fd_out)
{
    t_cmd   cmd;

    cmd = mini->cmd_data[index];
    if (!ft_strcmp(cmd.cmd_name, "cd"))
        return (ft_cd(mini, cmd.full_cmd));
    if (!ft_strcmp(cmd.cmd_name, "echo"))
        return (ft_echo(cmd.full_cmd, fd_out));
    if (!ft_strcmp(cmd.cmd_name, "env"))
        return (ft_env(mini, fd_out));
    if (!ft_strcmp(cmd.cmd_name, "exit"))
        return (ft_exit(mini, cmd.full_cmd));
    if (!ft_strcmp(cmd.cmd_name, "export"))
        return (ft_export(mini, cmd.full_cmd));
    if (!ft_strcmp(cmd.cmd_name, "pwd"))
        return (ft_pwd(mini));
    if (!ft_strcmp(cmd.cmd_name, "unset"))
        return (ft_unset(mini, cmd.full_cmd));
    return (EXIT_FAILURE);
}