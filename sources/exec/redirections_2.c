/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_process.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:41:41 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/17 12:57:09 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_do_redirections(t_var *mini, int index)
{
	if (ft_if_redir(mini, index))
	{
		ft_file_redirect(mini, index);
	}
	if (redirect_pipe_in(mini, index) == -1)
		exit(mini->status);
	if (redirect_pipe_out(mini, index) == -1)
		exit(mini->status);
}

int	ft_pipe_dup(int fd, int fileno, t_var *mini)
{
	if (fd == fileno && fd != -1)
		return (0);
	if (dup2(fd, fileno) == -1)
	{
		ft_error_msg("");
		mini->status = 1;
		close(fd);
		return (-1);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_pipe_in(t_var *mini, int index)
{
	return (ft_pipe_dup(mini->cmd_data[index].fd_in, STDIN_FILENO, mini));
}

int	redirect_pipe_out(t_var *mini, int index)
{
	return (ft_pipe_dup(mini->cmd_data[index].fd_out, STDOUT_FILENO, mini));
}
