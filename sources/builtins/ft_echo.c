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

int ft_check_nflag(char *arg)
{
    int i;

    i = 1;
    if(!ft_strncmp("-n", arg, 2))
    {
        while (arg[i] == 'n')
            i++;
        if (arg[i] == '\0')
            return (true);
    }
    return (false);
}
//make sure -nnnnnnn that is not single is also ignored!
int    ft_echo(char **args, int fd_out)
{
    bool    new_line;
    int     i;

    i = 1;
    new_line = 1;
    if (count_args(args) == 1)
    {
        ft_putstr_fd("\n", fd_out);
        return (EXIT_SUCCESS);
    }
    while (!ft_strncmp("-n", args[i], 2))
    {
        if (ft_check_nflag(args[i]))
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
