/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shlvl.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:05:32 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/13 16:27:57 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

int	ft_check_if_digits(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			break ;
		str++;
	}
	if (*str != '\0')
		return (true);
	return (false);
}

t_shlvl_status	ft_check_val_shlvl(char *val)
{
	long				value;
	t_shlvl_status		ret;

	ret = -1;
	value = ft_atol(val);
	if (value < 0)
		ret = SET_ZERO;
	else if (value == 999)
		ret = SET_NULL;
	else if (!ft_check_if_digits(val) && (value > INT_MAX || value < INT_MIN))
		ret = SET_ONE;
	else if (value > 999)
		ret = OUT_OF_BOUNDS; 
	else if (value >= 0 && value < 999)
		ret = INCREMENT;
	return (ret);
}

void	ft_change_node(t_env *env, char *new_val)
{
	free(env->value);
	env->value = ft_strdup(new_val);
}

void	ft_update_shlvl(t_shlvl_status ret, t_env *env)
{
	int	value;

	value = 0;
	if (ret == SET_ZERO)
		ft_change_node(env, "0");
	else if (ret == SET_ONE)
		ft_change_node(env, "1");
	else if (ret == SET_NULL)
		ft_change_node(env, NULL);
	else if (ret == INCREMENT)
	{
		value = ft_atoi(env->value) + 1;
		free(env->value);
		env->value = ft_itoa(value);
	}
	else if (ret == OUT_OF_BOUNDS)
	{
		ft_change_node(env, "1");
		ft_write_error(2, NULL, "warning", \
			"shell level too high, resetting to 1");
	}
	else
		ft_write_error(2, NULL, NULL, "error when setting shell level");
}

void	ft_add_to_env(t_var *mini, char *key, char *value)
{
	char *m_key;
	char *m_value;

	m_key = ft_strdup(key);
	if (!m_key)
		malloc_protect(mini);
	m_value = ft_strdup(value);
	if (!m_value)
	{
		free(m_key);
		malloc_protect(mini);
	}
	ft_add_node(mini->env_list, ft_new_node(m_key, m_value));
}

void	ft_set_shlvl(t_var *mini)
{
	t_env			*env;
	t_shlvl_status	ret;

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
