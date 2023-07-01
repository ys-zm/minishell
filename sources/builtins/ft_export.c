/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 12:52:50 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/01 01:48:21 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

t_env	*ft_new_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env) * 1);
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	ft_add_node(t_env **env_list, t_env *new_node)
{
	t_env	*env;

	env = *env_list;
	while (env->next != NULL)
		env = env->next;
	env->next = new_node;
}

void	ft_update_env_list(t_var *mini, char *key, char *value, size_t op_type)
{
	if (*(mini->env_list))
	{
		if (ft_check_if_key_exists(*(mini->env_list), key))
		{
			if (op_type == REPLACE && !ft_same(*(mini->env_list), key, value))
				ft_replace_value(mini, key, value);
			else if (op_type == APPEND)
				ft_append_value(mini, key, value);
		}
		else
			ft_add_node(mini->env_list, ft_new_node(key, value));
	}
	else
		*(mini->env_list) = ft_new_node(key, value);
}

int	ft_export_single(t_var *mini, char *arg, size_t op_type, size_t op_pos)
{
	char	*key;
	char	*value;

	if (op_type)
	{
		key = ft_substr(arg, 0, op_pos);
		if (ft_check_key(key))
			return (free(key), EXIT_FAILURE);
		value = ft_find_value(mini, arg, op_type, op_pos);
	}
	else
	{
		key = ft_substr(arg, 0, ft_strlen(arg));
		if (ft_check_key(key))
			return (free(key), EXIT_FAILURE);
		value = NULL;
	}
	ft_update_env_list(mini, key, value, op_type);
	return (EXIT_SUCCESS);
}

//a=b ignores the key for some reason
//expansion should work i.e. echo $new_key shold expand new_value
// export a="ls -la". run $a should run the cmd.
int	ft_export(t_var *mini, char **args)
{
	size_t	op_type;
	size_t	op_pos;
	int		i;

	i = 1;
	op_type = 0;
	op_pos = 0;
	if (!args[i])
		return (ft_print_export(mini->env_list), EXIT_SUCCESS);
	while (args && args[i])
	{
		op_type = ft_find_operator_type(args[i]);
		op_pos = ft_find_operator_pos(args[i]);
		ft_export_single(mini, args[i], op_type, op_pos);
		i++;
	}
	return (EXIT_SUCCESS);
}
