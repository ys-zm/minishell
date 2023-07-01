/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:25:57 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/01 01:48:21 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_del_node(t_env **env_list, char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!env_list)
		return ;
	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(curr->key)))
		{
			if (!prev)
				*env_list = curr->next;
			else
				prev->next = curr->next;
			return (free(curr->value), free(curr->key), free(curr));
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

//ft_unset: remove env variable from list
int	ft_unset(t_var *mini, char **args)
{
	int		i;
	t_env	*env;

	i = 1;
	if (mini->env_list)
		env = *(mini->env_list);
	if (!args[1])
		return (ft_write_error(2, "unset", NULL, "not enough arguments"), \
			EXIT_FAILURE);
	if (!env)
		return (EXIT_SUCCESS);
	while (args && args[i])
	{
		if (!ft_check_key(args[i], "unset"))
			ft_del_node(mini->env_list, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
