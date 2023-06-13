#include "minishell.h"

t_env   *ft_find_node(t_env *env_list, char *key)
{
    while (env_list->next != NULL)
    {
        if (!ft_strcmp(env_list->key, key))
            break ;
        env_list = env_list->next;
    }
    if (!ft_strcmp(env_list->key, key))
        return (env_list);
    else
        return (NULL);
}


int    ft_echo(char **args, int fd_out)
{
    bool    new_line;
    int     i;
    int     j;

    i = 1;
    new_line = 1;
    if (count_args(args) == 1)
    {
        ft_putstr_fd("\n", fd_out);
        return (EXIT_SUCCESS);
    }
    while (args[i] && args[i][0] == '-')
    {
        j = 1;
        while (args[i][j] == 'n')
            j++;
        if (args[i][j] == '\0')
            new_line = 0;
        else
            break ;
        i++;
    }
    while (args && args[i])
    {
        ft_putstr_fd(args[i], fd_out);
        if (args[i+1])
            ft_putstr_fd(" ", fd_out);
        i++;
    }
    if (new_line)
        ft_putstr_fd("\n", fd_out);
    return (EXIT_SUCCESS);
}
