/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 14:01:25 by yzaim         #+#    #+#                 */
/*   Updated: 2023/06/23 14:02:28 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
