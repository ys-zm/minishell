/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils_1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 11:57:18 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/11 15:08:42 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

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
