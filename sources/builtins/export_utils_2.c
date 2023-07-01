/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 14:01:25 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/01 01:48:21 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

int	ft_find_operator_type(char *env)
{
	int	i;

	i = 0;
	if (env[i] == '=')
		return (false);
	while (env[i] && env[i] != '=')
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
	if (env[i] == '=')
		return (REPLACE);
	return (false);
}

int	ft_find_operator_pos(char *env)
{
	int	i;

	i = 0;
	if (env[i] == '=')
		return (0);
	while (env && env[i] && env[i] != '=')
		i++;
	if (env[i] == '\0')
		return (0);
	if (env[i - 1] == '+')
		return (i - 1);
	if (env[i] == '=')
		return (i);
	return (0);
}

void	ft_print_export(t_env **env_list)
{
	t_env	*env;

	env = *env_list;
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		env = env->next;
	}
}
