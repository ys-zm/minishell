#include "minishell.h"

void    ft_free_all(t_var *mini)
{
    if (mini->cmd_data)
        ft_free_cmd_arr(mini->cmd_data, mini->n_cmd);
    ft_free_env_list(mini->env_list);
    if (mini->pipes)
        ft_free_pipes(mini->pipes, mini->n_cmd - 1);
    if (mini->paths)
        ft_free_strings(mini->paths);
    if (mini->pid)
        free(mini->pid);
    free(mini);
}

void	ft_error_msg(t_var *mini, char *str, int error)
{
    // it prints 'Success' when the function is called mistakenly, shall we decide to use a fixed error msg, like 'minishell: Memory fault'?
    (void)error;
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(str, 2);
	perror(str);
    mini->status = error;
}

//kill program when malloc fails
int    malloc_protect(t_var *mini, void *var)
{
    (void)var;
    remove_here_docs(mini);
    ft_free_all(mini);
    ft_error_msg(mini, "", 1);
    exit(1);
    return (mini->status = -1, mini->status);
}