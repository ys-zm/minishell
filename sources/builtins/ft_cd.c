/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 14:02:36 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/12 18:24:36 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

int	ft_run_chdir(t_var *mini, char *arg)
{
	char	*pwd;
	char	*new_pwd;
	char	*new_path;

	if (chdir(arg) == -1)
		return (ft_write_error(2, "cd", arg, "No such file or directory"), \
		EXIT_FAILURE);
	pwd = ft_find_env_val(mini->env_list, "PWD");
	if (!pwd)
		return (ft_write_error(2, "cd", NULL, "pwd not set"), 137);
	new_path = getcwd(0, 0);
	if (!new_path)
	{
		if (*arg != '/')
		{
			new_pwd = ft_strjoin(pwd, arg, "/", 0);
			if (!new_pwd)
				malloc_protect(mini);
			ft_update_env_var(mini, mini->env_list, "PWD", new_pwd);
			free(new_pwd);
		}
		else
		{
			ft_update_env_var(mini, mini->env_list, "PWD", pwd);
			free(pwd);
		}
		return (ft_write_error(2, "cd", NULL, "getcwd failed"), EXIT_SUCCESS);
	}
	ft_update_env_var(mini, mini->env_list, "OLDPWD", pwd);
	return (free(new_path), ft_update_env_var(mini, mini->env_list, "PWD", new_path), EXIT_SUCCESS);
}

int	ft_cd(t_var *mini, char **args)
{
	if (!args[1])
		return (ft_cd_to_homedir(mini, ft_find_env_val(mini->env_list, "PWD")));
	if (!ft_strncmp(args[1], "-", 1))
		return (ft_cd_to_oldpwd(mini, ft_find_env_val(mini->env_list, "PWD")));
	return (ft_run_chdir(mini, args[1]));
}
