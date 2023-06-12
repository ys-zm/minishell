#include "minishell.h"

t_env    *ft_new_node(char *key, char *value)
{
    t_env   *node;

    node = malloc(sizeof(t_env) * 1);
    if (!node)
        return (NULL);
    node->key = key;
    node->value = value;
    node->next = NULL;
    return (node);
}


void    ft_add_node(t_env *env_list, t_env *new_node)
{
    while (env_list->next != NULL)
    {
        env_list = env_list->next;
    }
    env_list->next = new_node;
}

void    ft_print_export(t_env *env_list)
{
    while (env_list)
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(env_list->key, 1);
        if (env_list->value)
        {
            ft_putstr_fd("=\"", 1);
            ft_putstr_fd(env_list->value, 1);
            ft_putstr_fd("\"\n", 1);
        }
        else
            ft_putstr_fd("\n", 1);
        env_list = env_list->next; 
    }
}

int ft_export_single(t_var *mini, char *arg, size_t op_type, size_t op_pos)
{
    
    char    *key;
    char    *value;
    
    if (op_type)
    {
        key = ft_substr(arg, 0, op_pos);
        if (ft_check_key(key))
            return (EXIT_FAILURE);
        value = ft_find_value(mini, arg, op_type, op_pos);
    }
    else
    {
        key = ft_substr(arg, 0, ft_strlen(arg));
        if (ft_check_key(key))
            return (EXIT_FAILURE);
        value = NULL;
    }
    if (mini->env_list)
    {
        if (ft_check_if_key_exists(mini->env_list, key))
        {
            if (op_type == REPLACE && !ft_check_if_same_value(mini->env_list, key, value))
                ft_replace_value(mini, key, value);
            else if (op_type == APPEND)
                ft_append_value(mini, key, value);
        }
        else
            ft_add_node(mini->env_list, ft_new_node(key, value));
    }
    else
        mini->env_list = ft_new_node(key, value);
    return (EXIT_SUCCESS);
}

int   ft_export(t_var *mini, char **args, int fd_out)
{
    size_t op_type = 0;
    size_t op_pos;
    int i;

    (void) fd_out;
    i = 1;
    if (!args[i])
        return (ft_print_export(mini->env_list), EXIT_SUCCESS);
    while (args && args[i])
    {
        op_type = ft_find_operator_type(args[i]);
        op_pos = ft_find_operator_pos(args[i]);
        if (ft_export_single(mini, args[i], op_type, op_pos))
            return (EXIT_FAILURE);
        i++;
    } 
    return (EXIT_SUCCESS);
}