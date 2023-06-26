/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:06:50 by yzaim         #+#    #+#                 */
/*   Updated: 2023/06/26 15:27:04 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Uilts for Adding to Env_List

int	ft_find_first_equals(char *env)
{
	int	i;

	i = 0;
	while (env && env[i] && env[i] != '=')
		i++;
	if (env[i] == '\0')
		return (0);
	return (i);
}

bool	ft_key_rules(char c, int index)
{
	if (index == 0)
	{
		if (ft_isalpha(c) || c == '_')
			return (true);
	}
	if (index > 0)
	{
		if (ft_isalnum(c) || c == '_')
			return (true);
	}
	return (false);
}

int	ft_check_key(char *key)
{
	int	i;

	i = 0;
	if (key && key[0] == '\0')
		return (ft_putstr_fd("minishell: export: `': not a valid identifier\n", \
				2), EXIT_FAILURE);
	while (key && key[i])
	{
		if (!ft_key_rules(key[i], i))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(key, 2);
			ft_putstr_fd("' : not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_find_data_if_no_pos(t_var *mini, char *envp, char **key, char **value)
{
	*key = ft_substr(envp, 0, ft_strlen(envp));
	if (!*key)
		malloc_protect(mini);
	if (ft_check_key(*key))
		return (free(*key), EXIT_FAILURE);
	*value = NULL;
	return (EXIT_SUCCESS);
}

t_env	*ft_create_node(t_var *mini, char *envp, int pos)
{
	char	*key;
	char	*value;

	if (pos)
	{
		key = ft_substr(envp, 0, pos);
		if (!key)
			malloc_protect(mini);
		if (ft_check_key(key))
			return (free(key), NULL);
		value = ft_substr(envp, pos + 1, ft_strlen(envp));
		if (!value)
		{
			free(key);
			malloc_protect(mini);
		}
	}
	else
	{
		if (ft_find_data_if_no_pos(mini, envp, &key, &value))
			return (NULL);
	}
	return (ft_new_node(key, value));
}
