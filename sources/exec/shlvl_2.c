/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shlvl_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:05:32 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/17 13:04:15 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_set_shlvl(t_var *mini)
{
	t_env			*env;
	t_shlvl_status	ret;

	if (!mini->env_list)
	{
		ft_add_to_env(mini, "SHLVL", "1");
		return ;
	}
	env = *(mini->env_list);
	ret = -1;
	if (ft_check_if_key_exists(*(mini->env_list), "SHLVL"))
	{
		while (env)
		{
			if (!ft_strcmp(env->key, "SHLVL"))
				break ;
			env = env->next;
		}
		ret = ft_check_val_shlvl(env->value);
		if (ret >= 0)
			ft_update_shlvl(ret, env);
	}
	else
		ft_add_to_env(mini, "SHLVL", "1");
}
