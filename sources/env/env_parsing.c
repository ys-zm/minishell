#include "minishell.h"

void    make_env_list(char **envp, t_var *mini)
{
    t_env   *new_node = NULL;
    t_env   *env_list;
    int i;
    i = 0;

    new_node = ft_envp_node(mini, envp[i++]); // if it is null it could also be because the key does not fit the right format
    if (!new_node)
        return ;    
    mini->env_list = new_node;
    env_list = new_node;
    while (envp && envp[i])
    {
        new_node = ft_envp_node(mini, envp[i]);
        if (!new_node)
            malloc_protect(mini, 0);
        env_list->next = new_node;
        env_list = env_list->next;
        i++;
    }
}