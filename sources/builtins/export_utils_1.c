/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils_1.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 14:01:18 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/17 12:28:19 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

int	ft_check_if_key_exists(t_env *env_list, char *key)
{
	t_env	*list;

	list = env_list;
	while (list)
	{
		if (ft_strcmp(list->key, key) == 0)
			return (true);
		list = list->next;
	}
	return (false);
}

void	ft_replace_value(t_var *mini, char *key, char *new_value)
{
	t_env	*list;

	list = *(mini->env_list);
	while (list)
	{
		if (ft_strcmp(list->key, key) == 0)
			break ;
		list = list->next;
	}
	if (list)
	{
		free(list->value);
		list->value = new_value;
		if (!list->value)
			malloc_protect(mini);
	}
}

void	ft_append_value(t_var *mini, char *key, char *to_add)
{
	t_env	*list;
	char	*new_value;

	new_value = NULL;
	list = *(mini->env_list);
	while (list)
	{
		if (ft_strcmp(list->key, key) == 0)
			break ;
		list = list->next;
	}
	if (list)
	{
		new_value = ft_strjoin(list->value, to_add, "", 0);
		free(to_add);
		if (!new_value)
			malloc_protect(mini);
		free(list->value);
		list->value = new_value;
	}
}

char	*ft_find_value(t_var *mini, char *arg, size_t op_type, size_t op_pos)
{
	char	*value;

	if (op_type == APPEND)
		op_pos++;
	if (op_pos == ft_strlen(arg))
		value = ft_strdup("");
	else
		value = ft_substr(arg, op_pos + 1, ft_strlen(arg));
	if (!value)
		malloc_protect(mini);
	return (value);
}
