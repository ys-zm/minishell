/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 11:57:18 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/17 12:40:29 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

int	ft_cd_to_homedir(t_var *mini, char *cwd)
{
	char	*new_path;

	new_path = ft_find_env_val(mini->env_list, "HOME");
	if (!new_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	if (!chdir(new_path))
	{
		ft_update_env_var(mini, mini->env_list, "OLDPWD", cwd);
		ft_update_env_var(mini, mini->env_list, "PWD", new_path);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_write_error(2, "cd", new_path, "No such file or directory");
		return (EXIT_FAILURE);
	}
}

int	ft_cd_to_oldpwd(t_var *mini, char *cwd)
{
	char	*old_pwd;

	old_pwd = ft_find_env_val(mini->env_list, "OLDPWD");
	if (!old_pwd)
		return (ft_write_error(2, "cd", NULL, "OLDPWD not set"), \
		EXIT_FAILURE);
	if (!chdir(old_pwd))
	{
		return (ft_update_env_var(mini, mini->env_list, "OLDPWD", cwd), \
		ft_update_env_var(mini, mini->env_list, "PWD", old_pwd), EXIT_SUCCESS);
	}
	else
		return (ft_write_error(2, "cd", old_pwd, "No such file or directory"), \
		EXIT_FAILURE);
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

char	*ft_find_env_val(t_env **env_list, char *env_var)
{
	t_env		*env;
	size_t		len;

	if (!env_list)
		return (NULL);
	env = *env_list;
	len = ft_strlen(env_var);
	while (env)
	{
		if (!ft_strncmp(env->key, env_var, len))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_update_env_var(t_var *mini, t_env **env_list, \
		char *which_env, char *new_env)
{
	t_env	*env;

	if (env_list && ft_check_if_key_exists(*env_list, which_env))
	{
		env = *env_list;
		while (env)
		{
			if (!ft_strcmp(env->key, which_env))
				break ;
			env = env->next;
		}
		free(env->value);
		env->value = ft_strdup(new_env);
		if (!env->value)
			malloc_protect(mini);
	}
	else
		ft_add_to_env(mini, which_env, new_env);
}
