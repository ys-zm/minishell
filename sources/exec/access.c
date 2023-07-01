/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   access.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:29:37 by yzaim         #+#    #+#                 */
/*   Updated: 2023/06/26 16:46:15 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_find_error(t_var *mini, char *cmd)
{
	char	*cmd_path;
	int		i;
	int		found;

	found = 0;
	i = 0;
	while (mini->paths && mini->paths[i])
	{
		cmd_path = ft_trip_join(mini->paths[i++], "/", cmd);
		if (!cmd_path)
			malloc_protect(mini);
		if (access(cmd_path, F_OK) == 0)
		{
			found = 1;
			break ;
		}
		if (cmd_path)
		{
			free(cmd_path);
			cmd_path = NULL;
		}
	}
	ft_call_error(mini, cmd, cmd_path, found);
}

char	*check_env_paths(t_var *mini, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = NULL;


	while (mini->paths && mini->paths[i])
	{
		cmd_path = ft_trip_join(mini->paths[i], "/", cmd);
		if (!cmd_path)
			malloc_protect(mini);
		if (!access(cmd_path, X_OK))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	ft_find_error(mini, cmd);
	return (NULL);
}

char	*check_cwd(t_var *mini, char *cmd)
{
	char	*cmd_path;

	cmd_path = ft_strjoin("./", cmd, "", false);
	if (cmd_path)
	{
		if (!access(cmd_path, F_OK))
		{
			if (!access(cmd_path, X_OK))
				return (cmd_path);
			else
			{
				free(cmd_path);
				cmd_path = NULL;
				ft_permission_denied(mini, cmd);
			}
		}
	}
	free(cmd_path);
	return (NULL);
}

char	*find_cmd_path(t_var *mini, char *cmd)
{
	char	*cmd_path;

	if (cmd && *cmd == '\0')
		ft_command_not_found(mini, cmd);
	if (ft_is_path(cmd))
		return (cmd);
	if (ft_if_path_exists(mini))
	{
		if (mini->paths)
		{
			cmd_path = check_env_paths(mini, cmd);
			if (cmd_path)
				return (cmd_path);
			free(cmd_path);
		}
	}
	else
	{
		cmd_path = check_cwd(mini, cmd);
		if (cmd_path)
			return (cmd_path);
		free(cmd_path);
	}
	return (ft_command_not_found(mini, cmd), NULL);
}

char	*access_cmd_path(t_var *mini, char *cmd)
{
	char	*cmd_path;

	ft_split_path(mini);
	cmd_path = find_cmd_path(mini, cmd);
	if (cmd_path)
	{
		ft_set_shlvl(mini, cmd);
		mini->env_arr = ft_list_to_arr(mini, *(mini->env_list));
	}
	return (cmd_path);
}
