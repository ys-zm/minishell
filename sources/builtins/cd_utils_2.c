/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils_2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 12:31:00 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/01 01:48:21 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

int	ft_count_directories(char *arg)
{
	int	count;
	int	flag;

	flag = 1;
	count = 0;
	while (*arg == '/')
		arg++;
	while (arg && *arg)
	{
		if (*arg != '/')
			flag = 1;
		if (*arg == '/' && flag == 1)
		{
			flag = 0;
			count++;
		}
		arg++;
	}
	if (flag == 1 && !*arg)
		count++;
	if (!count)
		return (1);
	return (count);
}

t_env	*ft_search_env_var(t_env **env_list, char *which_env)
{
	t_env	*env;

	env = *env_list;
	while (env)
	{
		if (!ft_strncmp(which_env, env->key, ft_strlen(which_env)))
			break ;
		env = env->next;
	}
	return (env);
}

void	ft_update_env_var(t_var *mini, t_env **env_list, \
		char *which_env, char *new_env)
{
	t_env	*env_var;

	env_var = ft_search_env_var(env_list, which_env);
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ft_strdup(new_env);
		if (!env_var->value)
			malloc_protect(mini);
	}
}
