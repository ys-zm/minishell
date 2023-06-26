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
			new_path = ft_strjoin(ret, args[i], "/", 0);
			if (!new_path)
				malloc_protect(mini);
			if (access(new_path, F_OK))
				return (ft_free_strings(args), free(ret), free(new_path), NULL);
			free(ret);
			ret = new_path;
		}
		i++;
	}
	ft_free_strings(args);
	return (ret);
}

//ft_cd: change directory
//I dont get the behaviour of cd when you delete a directory two times above
//i.e mkdir 1/2
// mkdir 1/2/3
// mkdir 1/2/3/4
// cd 1/2/3/4
// rm -rf ../../../../1
int ft_cd(t_var *mini, char **args)
{
	char	*cwd;
	char	*new_path;

	cwd = getcwd(0, 0);
	if (!ft_strcmp(args[1], "."))
		return (free(cwd), EXIT_SUCCESS);
	if (count_args(args) == 1)
		return (free(cwd), ft_cd_to_homedir(mini, cwd));
	if (!ft_strncmp("-", args[1], 1))
		return (free(cwd), ft_cd_to_oldpwd(mini, cwd));
	if (args[1][0] == '/')
		new_path = ft_strdup(args[1]);
	else
		new_path = ft_calculate_path(mini, args[1], cwd);
	if (!chdir(new_path))
	{
		ft_update_env_var(mini->env_list, "OLDPWD", cwd);
		ft_update_env_var(mini->env_list, "PWD", new_path);
		return (free(cwd), free(new_path), EXIT_SUCCESS);
	}
	else
	{
		free(new_path);
		free(cwd);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		return (ft_putstr_fd(": No such file or directory\n", 2), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}