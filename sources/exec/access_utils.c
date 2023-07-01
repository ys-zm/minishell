/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   access_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:41:15 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/01 01:48:12 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_call_error(t_var *mini, char *cmd, char *cmd_path, int found)
{
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

bool	ft_is_path(char *cmd)
{
	while (cmd && *cmd)
	{
		if (*cmd == '/')
			return (true);
		cmd++;
	}
	return (false);
}

bool	ft_if_path_exists(t_var *mini)
{
	t_env	*env;

	env = *(mini->env_list);
	while (env)
	{
		if (!strncmp(env->key, "PATH", 4))
			return (true);
		env = env->next;
	}
	return (false);
}
