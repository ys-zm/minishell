#include "minishell.h"

int    ft_del_node(t_var *mini, char *key)
{
    t_env   *env_list;
    t_env   *prev;
    t_env   *next;
    t_env   *curr;

    env_list = *(mini->env_list);
    curr = env_list;
    prev = NULL;
    next = env_list->next;
    if (curr->key && !ft_strcmp(curr->key, key))
    {
        free(curr);
        *(mini->env_list) = next;
    }
    else
    {
        while (curr)
        {
            if (!ft_strcmp(curr->key, key))
                break ;
            prev = curr;
            curr = curr->next;
            next = curr->next;
        }
    }
    if (curr && !ft_strcmp(curr->key, key))
    {
        prev->next = next; //segfault bait
        free(curr); //its a struct
    }
    return (EXIT_FAILURE);
}

//ft_unset: remove env variable from list
//if its the head, set new head
int    ft_unset(t_var *mini, char *key, int fd_out)
{
    (void)fd_out;

    if (ft_del_node(mini, key))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}