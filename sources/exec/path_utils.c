#include "minishell.h"

void    ft_command_not_found(t_var *mini, char *cmd)
{
    (void) mini;
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(": command not found\n", STDERR_FILENO);
    ft_free_all(mini);
    exit (127);
}

void    ft_permission_denied(t_var *mini, char *cmd)
{
    (void) mini;
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
    ft_free_all(mini);
    exit (126);
}