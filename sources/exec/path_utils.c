#include "minishell.h"

void    ft_command_not_found(char *cmd)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(": command not found\n", STDERR_FILENO);
    exit (127);
}

void    ft_permission_denied(char *cmd)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
    exit (126);
}