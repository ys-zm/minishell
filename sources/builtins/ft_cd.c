/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 14:02:36 by yzaim         #+#    #+#                 */
/*   Updated: 2023/06/23 21:37:17 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_calculate_path(t_var *mini, char *arg, char *curr_path)
{
	size_t	i;
	char	*new_path;
	char	*ret;
	char	**args;

	new_path = NULL;
	ret = ft_strdup(curr_path);
	if (!ret)
		malloc_protect(mini);
	args = ft_split(arg, '/', 0);
	if (!args)
		malloc_protect(mini);
	i = 0;
	while (args && args[i])
	{
		if (!ft_strncmp(args[i], "..", 2))
		{
			new_path = ft_remove_lastdir(mini, ret);
			free(ret);
			ret = new_path;
		}
		else
		{
			if (i > 0)
				new_path = ft_strjoin(ret, args[i], "/", 0);
			else
				new_path = ft_strjoin(ret, args[i], "", 0);
			if (!new_path)
				malloc_protect(mini);
			if (access(new_path, F_OK))
			{
				free(ret);
				free(new_path);
				return (NULL);
			}
			free(ret);
			ret = new_path;
		}
		i++;
	}
	ft_free_strings(args);
	return (ret);
}

//ft_cd: change directory
//fix .. setting old pwd and pwd when you do ..
int ft_cd(t_var *mini, char **args) //update the envp for PWD and OLDPWD, but only if they exist
{
	char	*cwd;
	char	*new_path;

	cwd = getcwd(0, 0);
	if (!cwd)
		ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
	ft_update_env_var(mini->env_list, "OLDPWD", cwd);
	if (count_args(args) == 1)
		return (ft_cd_to_homedir(mini));	
	if (!ft_strcmp(args[1], "."))
		return (EXIT_SUCCESS);
	if (!ft_strncmp("-", args[1], 1))
		return (ft_cd_to_oldpwd(mini)); //not working!
	if (args[1][0] == '/')
	{
		free(cwd);
		cwd = ft_strdup("/");
	}
	new_path = ft_calculate_path(mini, args[1], cwd);
	free(cwd);
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
	return (EXIT_SUCCESS);
}
