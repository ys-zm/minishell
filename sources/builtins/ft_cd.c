/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 14:02:36 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/08 01:33:58 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

bool	ft_check_err_new_path(t_var *mini, char *new_path)
{
	if (!new_path)
		malloc_protect(mini);
	if (access(new_path, F_OK))
		return (false);
	return (true);
}

char	*ft_path_finder(t_var *mini, char *curr_path, char **args)
{
	size_t	i;
	char	*new_path;

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
			if (!ft_check_err_new_path(mini, new_path))
				return (free(curr_path), free(new_path), NULL);
			free(curr_path);
			curr_path = new_path;
		}
		i++;
	}
	return (curr_path);
}

char	*ft_calculate_path(t_var *mini, char *arg, char *curr_path)
{
	char	**args;
	char	*ret;

	args = ft_split(arg, '/', 0);
	if (!args)
		malloc_protect(mini);
	ret = ft_path_finder(mini, curr_path, args);
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
int	ft_cd(t_var *mini, char **args)
{
	char	*cwd;
	char	*new_path;

	cwd = getcwd(0, 0);
	if (!cwd)
		ft_error_msg(mini, "cd", 0);
	if (args[1] && !ft_strcmp(args[1], "."))
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
		ft_update_env_var(mini, mini->env_list, "OLDPWD", cwd);
		ft_update_env_var(mini, mini->env_list, "PWD", new_path);
		return (free(new_path), EXIT_SUCCESS);
	}
	else
		return (free(new_path), \
		ft_write_error(2, "cd", args[1], "No such file or directory"), \
		EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
