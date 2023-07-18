/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:30:46 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/18 22:55:02 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

int	ft_free_strings(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		ft_free(arr[i]);
		i++;
	}
	ft_free(arr);
	return (EXIT_SUCCESS);
}

int	ft_free_pipes(int **pipes, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_free(pipes[i]);
		i++;
	}
	ft_free(pipes);
	return (EXIT_SUCCESS);
}

int	ft_free_cmd_struct(t_cmd *cmd)
{
	if (cmd->full_cmd)
		ft_free_strings(cmd->full_cmd);
	if (cmd->n_redirect)
		ft_free(cmd->redirections);
	if (cmd->files)
		ft_free_strings(cmd->files);
	return (EXIT_SUCCESS);
}

int	ft_free_cmd_arr(t_var *mini)
{
	uint32_t	i;

	i = 0;
	while (i < mini->n_cmd)
	{
		ft_free_cmd_struct(mini->cmd_data + i);
		i++;
	}
	ft_free(mini->cmd_data);
	mini->cmd_data = NULL;
	mini->n_cmd = 0;
	return (EXIT_SUCCESS);
}

int	ft_free_env_list(t_var *mini)
{
	t_env	*tmp;
	t_env	**env_list;

	if (!mini->env_list)
		return (EXIT_SUCCESS);
	env_list = mini->env_list;
	while (*env_list != NULL)
	{
		tmp = *env_list;
		*env_list = (*env_list)->next;
		ft_free(tmp->key);
		ft_free(tmp->value);
		ft_free(tmp);
	}
	ft_free(env_list);
	return (EXIT_SUCCESS);
}
