/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:14:36 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/01 01:48:21 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

// free all allocated memory
void	ft_set_to_null(t_var *mini)
{
	mini->cmd_data = NULL;
	mini->pipes = NULL;
	mini->paths = NULL;
	mini->env_arr = NULL;
	mini->pid = NULL;
	mini->env_list = NULL;
}

void	ft_free_all(t_var *mini)
{
	if (mini->cmd_data)
		ft_free_cmd_arr(mini->cmd_data, mini->n_cmd);
	ft_free_env_list(mini);
	if (mini->pipes)
	{	
		ft_free_pipes(mini->pipes, mini->n_cmd - 1);
	}	
	if (mini->paths)
	{
		ft_free_strings(mini->paths);
	}
	if (mini->env_arr)
		ft_free_strings(mini->env_arr);
	if (mini->pid)
		free(mini->pid);
	free(mini);
	ft_set_to_null(mini);
}

// print error message from minishell and set g_exit_code
// function does not exit
void	ft_error_msg(t_var *mini, char *str, int error)
{
	(void)mini;
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	g_exit_code = error;
}

// kill program when malloc fails, sets exit code to 1
int	malloc_protect(t_var *mini)
{
	// remove_here_docs();
	ft_free_all(mini);
	ft_error_msg(mini, "", 137);
	exit(g_exit_code);
}
