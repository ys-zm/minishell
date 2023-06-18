#include "minishell.h"

//error if the command in spelt: echp
void	ft_find_error(t_var *mini, char *cmd)
{
	char	*cmd_path = NULL;
	int	i;
	int	found;

	found = 0;
	i = 0;
	while (mini->paths && mini->paths[i])
	{
		cmd_path = ft_trip_join(mini->paths[i], "/", cmd);
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
		i++;
	}
	if (found == 0)
	{
		if (cmd_path)
			free(cmd_path);
		ft_command_not_found(mini, cmd);
	}
	else if (found == 1 && access(cmd_path, X_OK) == -1)
	{
		if (cmd_path)
			free(cmd_path);
		ft_permission_denied(mini, cmd);
	}
}

char	*check_env_paths(t_var *mini, char *cmd)
{
	char	*cmd_path;
	int	i;

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

bool	check_absolute_path(char *cmd)
{
	if (!access(cmd, X_OK))
		return (true);
	return (false);
}

char	*access_cmd_path(t_var *mini, char *cmd)
{
	char	*cmd_path;

	cmd_path = NULL;
	ft_split_path(mini);
	if (check_absolute_path(cmd))
		return (cmd);
	cmd_path = check_cwd(mini, cmd);
	if (cmd_path)
		return (cmd_path);
	if (mini->paths)
	{
		cmd_path = check_env_paths(mini, cmd);
		printf("cmd path: %s\n", cmd_path);
		if (cmd_path)
			return (cmd_path);
		free(cmd_path);
	}
	// ft_free_strings(mini->paths);
	return (NULL);
}
