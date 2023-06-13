#include "minishell.h"

char *ft_remove_lastdir(char *old_path)
{
    int     len;
    int     i;
    char    *new_path;

    len = ft_strlen(old_path);
    i = len - 1;
    while (i >= 0)
    {
        if (old_path[i] == '/')
            break ;
        i--;
    }
    new_path = ft_substr(old_path, 0, i + 1);
    return (new_path);
}

char    *ft_get_home(t_var *mini)
{
    t_env   **env;

    env = mini->env_list;
    while ((*env)->next && ft_strncmp((*env)->key, "HOME", 4))
        *env = (*env)->next;
    if (ft_strncmp((*env)->key, "HOME", 4))
    {
        ft_putstr_fd("cd: HOME not set", 2);
        return (NULL);
    }
    return ((*env)->value);
}

t_env   *ft_search_env_var(t_env **env_list, char *which_env)
{
    t_env   *env;

    env = *env_list;
    while (env)
    {
        if (!ft_strncmp(which_env, env->key, ft_strlen(which_env)))
            break ;
        env = env->next;
    }
    return (env);
}

void ft_update_env_var(t_env **env_list, char *which_env, char *new_env)
{
    t_env   *env_var;

    env_var = ft_search_env_var(env_list, which_env);
    if (env_var)
    {
        free(env_var->value);
        env_var->value = ft_strdup(new_env);
    }
}

//ft_cd: change directory
//issues:
int ft_cd(t_var *mini, char **args, int fd_out) //update the envp for PWD and OLDPWD, but only if they exist
{
    char    *cwd;
    char    *new_path;

    (void)fd_out;
    cwd = getcwd(0, 0);
    ft_update_env_var(mini->env_list, "OLDPWD", cwd);
    if (count_args(args) == 1)
    {
        new_path = ft_get_home(mini);
        if (!new_path)
            return (EXIT_FAILURE);
        if (!chdir(new_path))
            return (EXIT_SUCCESS);
    }
    if (!ft_strcmp(args[1], "."))
        return (EXIT_SUCCESS);
    if (!chdir(args[1]))
    {
        ft_update_env_var(mini->env_list, "PWD", args[1]);
        return (EXIT_SUCCESS);
    }
    if (!ft_strcmp(args[1], ".."))
        new_path = ft_remove_lastdir(cwd);
    else
        new_path = ft_trip_join(cwd, "/", args[1]);
    if (!chdir(new_path))
    {
        ft_update_env_var(mini->env_list, "PWD", new_path);
        return (EXIT_SUCCESS);
    }
    else
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(args[1], 2);
        return (ft_putstr_fd(": No such file or directory\n", 2), EXIT_FAILURE);
    }
}