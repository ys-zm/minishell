#include "minishell.h"

int    ft_del_node(t_env *env_list, char *key)
{
    t_env   *prev;
    
    prev = NULL;
    while (env_list)
    {
        if (!ft_strcmp(env_list->key, key))
            break ;
        prev = env_list;
        env_list = env_list->next;
    }
    if (env_list && !ft_strcmp(env_list->key, key))
    {
        prev->next = env_list->next; //segfault bait
        free(env_list); //its a struct
    }
    return (EXIT_FAILURE);
}

//ft_unset: remove env variable from list
int    ft_unset(t_var *mini, char *key, int fd_out)
{
    (void)fd_out;
    if (ft_del_node(mini->env_list, key))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}