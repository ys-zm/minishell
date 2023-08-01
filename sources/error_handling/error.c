/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:14:36 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/18 22:50:24 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

// free all allocated memory
void	ft_set_to_null(t_var *mini)
{
	mini->cmd_data = NULL;
	mini->paths = NULL;
	mini->env_arr = NULL;
	mini->env_list = NULL;
	mini->hd_path = NULL;
}

void	ft_free_all(t_var *mini)
{
	if (mini->cmd_data)
		ft_free_cmd_arr(mini);
	if (mini->env_list)
		ft_free_env_list(mini);
	if (mini->paths)
		ft_free_strings(mini->paths);
	if (mini->env_arr)
		ft_free_strings(mini->env_arr);
	ft_free(mini->hd_path);
	ft_set_to_null(mini);
	free(mini);
}

// print error message from minishell and set g_exit_code
// function does not exit
void	ft_error_msg(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	perror(str);
}

// kill program when malloc fails, sets exit code to 1
int	malloc_protect(t_var *mini)
{
	remove_here_docs(mini->hd_path);
	ft_free_all(mini);
	ft_error_msg("");
	g_exit_code = 137;
	exit(g_exit_code);
}

void	ft_write_error(int fd, char *func, char *str, char *msg)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(func, fd);
	ft_putstr_fd(": ", fd);
	if (str)
	{
		ft_putstr_fd(str, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
}
