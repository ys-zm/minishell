#include "minishell.h"

int ft_find_operator_type(char *env)
{
    int i;

    i = 0;
    if (env[i] == '=')
        return (false);
    while (env && env[i] && env[i] != '=')
        i++;
    if (env[i] == '\0')
        return (false);
    if (env[i - 1] == '+')
    {
        if (i == 1)
            return (false);
        else
            return (APPEND);
    }
    if (env[i] == '=' && env[i - 1] == '+')
        return (REPLACE);
    return (false);
}

int ft_find_operator_pos(char *env)
{
    int i;

    i = 0;
    if (env[i] == '=')
        return (0);
    while (env && env[i] && env[i] != '=')
        i++;
    if (env[i] == '\0')
        return (0);
    if (env[i - 1] == '+')
        return (i - 1);
    if (env[i] == '=' && env[i - 1] == '+')
        return (i);
    return (0);
}

int ft_check_if_same_value(t_env *env_list, char *key, char *value)
{
    t_env   *list;

    list = env_list;
    while (list)
    {
        if (ft_strcmp(list->key, key) == 0)
            break ;
        list = list->next;
    }
    if (list && list->value && ft_strcmp(list->value, value) == 0)
        return (true);
    return (false);
}

int ft_check_if_key_exists(t_env *env_list, char *key)
{
    t_env   *list;

    list = env_list;
    while (list)
    {
        if (ft_strcmp(list->key, key) == 0)
            return (true);
        list = list->next;
    }
    return (false);
}

void    ft_replace_value(t_var *mini, char *key, char *new_value)
{
     t_env   *list;

    list = mini->env_list;
    while (list)
    {
        if (ft_strcmp(list->key, key) == 0)
            break ;
        list = list->next;
    }
    if (list)
    {
        free(list->value);
        list->value = ft_strdup(new_value);
        if (!list->value)
            malloc_protect(mini, NULL);
    }
}

void    ft_append_value(t_var *mini, char *key, char *to_add)
{
    t_env   *list;
    char    *new_value;

    new_value = NULL;
    list = mini->env_list;
    while (list)
    {
        if (ft_strcmp(list->key, key) == 0)
            break ;
        list = list->next;
    }
    if (list)
    {
        new_value = ft_strjoin(list->value, to_add, "", 0);
        if (!new_value)
        {
            free(to_add);
            malloc_protect(mini, NULL);
        }
        free(to_add);
        free(list->value);
        list->value = new_value;
       
    }
}

char    *ft_find_value(t_var *mini, char *arg, size_t op_type, size_t op_pos)
{
    char *value;

    if (op_type == APPEND)
        op_pos++;
    if (op_pos == ft_strlen(arg))
        value = ft_strdup("");
    else
        value = ft_substr(arg, op_pos + 1, ft_strlen(arg));
    if (!value)
        malloc_protect(mini, NULL);
    return (value);
}