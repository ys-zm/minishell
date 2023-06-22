#include "minishell.h"

int ft_check_if_minishell(char *cmd)
{
    if (cmd && !ft_strncmp("./minishell", cmd, 11))
        return (true);
    return (false);
}

// void    ft_fork_new_shell(t_var *mini)
// {
//     int fork;
// }