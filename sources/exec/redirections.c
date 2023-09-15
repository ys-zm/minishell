/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:49:24 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/17 11:45:08 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

bool	ft_if_redir(t_var *mini, int index)
{
	t_cmd	cmd;

	cmd = mini->cmd_data[index];
	if (!cmd.redirections && !cmd.files)
		return (false);
	return (true);
}

bool	ft_check_permission(t_cmd *cmd, t_red_type red_type, int index)
{
	if (red_type == RED_IN_SINGLE || red_type == RED_IN_DOUBLE)
	{
		cmd->fd_in = open(cmd->files[index], O_RDONLY);
		if (cmd->fd_in == -1)
			return (EXIT_FAILURE);
	}
	if (red_type == RED_OUT_SINGLE)
	{
		cmd->fd_out = open(cmd->files[index], O_WRONLY | O_TRUNC | O_CREAT, \
			0664);
		if (cmd->fd_out == -1)
			return (EXIT_FAILURE);
	}
	if (red_type == RED_OUT_DOUBLE)
	{
		cmd->fd_out = open(cmd->files[index], O_WRONLY | O_APPEND | O_CREAT, \
			0664);
		if (cmd->fd_out == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_redir_type(t_var *mini, int index)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = mini->cmd_data + index;
	while (cmd->files && cmd->files[i])
	{
		if (ft_check_permission(cmd, cmd->redirections[i], i) == EXIT_FAILURE)
		{
			ft_error_msg(cmd->files[i]);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_file_redirect(t_var *mini, int index)
{
	if (ft_redir_type(mini, index))
	{
		mini->status = 1;
		exit(mini->status);
	}
	return (EXIT_SUCCESS);
}
