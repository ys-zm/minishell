/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shlvl.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:05:32 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/11 16:00:36 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_increment_shlvl(t_var *mini)
{
	t_env	*env_list;
	int		value;

	env_list = *(mini->env_list);
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, "SHLVL"))
			break ;
		env_list = env_list->next;
	}
	if (env_list)
	{
		value = ft_atoi(env_list->value);
		value += 1;
		free(env_list->value);
		env_list->value = ft_itoa(value);
	}
}

// int	ft_check_val_shlvl(t_var *mini)
// {
// 	t_env	*env_list;
// 	long	value;
// 	int		ret = 0;

// 	env_list = *(mini->env_list);
// 	while (env_list)
// 	{
// 		if (!ft_strcmp(env_list->key, "SHLVL"))
// 			break ;
// 		env_list = env_list->next;
// 	}
// 	if (env_list)
// 	{
// 		value = ft_atol(env_list->value);
// 		if (value > INT_MIN && value < 0)
// 			ret = SET_ZERO;
// 		else if (value == 999)
// 			ret = SET_NULL;
// 		else if (value > 999 && value < INT_MAX)
// 			ret = SET_ONE;
// 		else if (value > 0 && value < 999)
// 			ret = INCREMENT;
// 		else
// 			ret = OUT_OF_BOUNDS;	
// 	}
// 	return (ret);
// }

void	ft_set_shlvl(t_var *mini)
{
	
	if (ft_check_if_key_exists(*(mini->env_list), "SHLVL"))
	{
			ft_increment_shlvl(mini);	
	}
	else
		ft_add_node(mini->env_list, ft_new_node("SHLVL", "1"));
}