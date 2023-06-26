/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils_1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 11:57:18 by yzaim         #+#    #+#                 */
/*   Updated: 2023/06/26 12:04:17 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_lastdir(t_var *mini, char *old_path)
{
	int		len;
	int		i;
	char	*new_path;

	i = 0;
	len = ft_strlen(old_path);
	if (!len)
		return (NULL);
	i = len - 1;
	if (old_path[i] == '/')
		i--;
	while (i >= 0)
	{
		if (old_path[i] == '/')
			break ;
		i--;
	}
	new_path = ft_substr(old_path, 0, i + 1);
	if (!new_path)
		malloc_protect(mini);
	return (new_path);
}

char	*ft_get_home(t_var *mini)
{
	t_env	*env;

	env = *(mini->env_list);
	while (env)
	{
		if (!ft_strncmp(env->key, "HOME", 4))
			return (env->value);
		env = env->next;
	}
	return (NULL);
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

void	ft_update_env_var(t_env **env_list, char *which_env, char *new_env)
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

int	ft_cd_to_homedir(t_var *mini, char *cwd)
{
	char	*new_path;

	new_path = ft_get_home(mini);
	if (!new_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	if (!chdir(new_path))
	{
		ft_update_env_var(mini->env_list, "OLDPWD", cwd);
		ft_update_env_var(mini->env_list, "PWD", new_path);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(new_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
}

int	ft_cd_to_oldpwd(t_var *mini, char *cwd)
{
	char	*old_pwd;
	t_env	*env;

	env = *(mini->env_list);
	while (env)
	{
		if (env && !ft_strncmp(env->key, "OLDPWD", 6))
		{
			old_pwd = env->value;
			break ;
		}
		env = env->next;
	}
	if (!env)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		retrun (EXIT_FAILURE);
	}
	if (!chdir(old_pwd))
	{
		ft_update_env_var(mini->env_list, "OLDPWD", cwd);
		return (ft_update_env_var(mini->env_list, "PWD", old_pwd), EXIT_SUCCESS;
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(old_pwd, 2);
		return (ft_putstr_fd(": No such file or directory\n", 2), EXIT_FAILURE);
	}
}

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
