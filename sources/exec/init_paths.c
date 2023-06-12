#include "minishell.h"

char *ft_find_path(t_var *mini)
{
    t_env   *env_list;

    env_list = mini->env_list;
    while (env_list->next != NULL)
    {
        if (!ft_strncmp(env_list->key, "PATH", 4))
            break ;
        env_list = env_list->next;
    }
    if (!ft_strncmp(env_list->key, "PATH", 4))
        return (env_list->value);
    return (NULL);
}

void ft_split_path(t_var *mini)
{
    char    *path_value;

    path_value = ft_find_path(mini);
    if (path_value)
    {
        mini->paths = ft_split(path_value, ':', false);
        if (!mini->paths)
        {
            free(mini->paths);
            malloc_protect(mini, NULL);
        }
        return ;
    }
    mini->paths = NULL;
}
