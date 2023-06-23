/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 14:02:36 by yzaim         #+#    #+#                 */
/*   Updated: 2023/06/23 15:11:06 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_calculate_path(t_var *mini, char *arg, char *curr_path)
{
	size_t	i;
	char	*new_path;
	char	**args;

	args = ft_split(arg, '/', 0);	
	i = 0;
	while (args && args[i])
	{
		if (!ft_strncmp(args[i], "..", 2))
		{
			new_path = ft_remove_lastdir(mini, curr_path);
			free(curr_path);
			curr_path = new_path;
		}
		else
		{
			new_path = ft_strjoin(curr_path, args[i], "/", 0);
			free(curr_path);
			curr_path = new_path;
		}
		i++;
	}
	new_path = ft_strjoin("/", curr_path, "", 0);
	free(curr_path);
	curr_path = new_path;
	return (curr_path);
}

//ft_cd: change directory
//fix .. setting old pwd and pwd when you do ..
int ft_cd(t_var *mini, char **args) //update the envp for PWD and OLDPWD, but only if they exist
{
	char	*cwd;
	char	*new_path;

	cwd = getcwd(0, 0);
		if (!cwd)
			return (ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2), EXIT_SUCCESS);
	ft_update_env_var(mini->env_list, "OLDPWD", cwd);
	if (count_args(args) == 1)
		return (ft_cd_to_homedir(mini));	
	if (!ft_strncmp("-", args[1], 1))
		return (ft_cd_to_oldpwd(mini));
	if (!ft_strcmp(args[1], "."))
		return (EXIT_SUCCESS);
	if (args[1][0] == '/')
		cwd = NULL;
	new_path = ft_calculate_path(mini, args[1], cwd);
	if (!chdir(new_path))
	{
		ft_update_env_var(mini->env_list, "PWD", new_path);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		return (ft_putstr_fd(": No such file or directory\n", 2), EXIT_FAILURE);
    }
	free(cwd);
	return (0);
}
