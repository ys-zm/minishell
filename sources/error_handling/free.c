#include "minishell.h"

int	ft_free_strings(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (EXIT_SUCCESS);
}

int	ft_free_pipes(int **pipes, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	return (EXIT_SUCCESS);
}

int	ft_free_cmd_struct(t_cmd *cmd)
{
	if (cmd->full_cmd)
		ft_free_strings(cmd->full_cmd);
	if (cmd->n_redirect)
		free(cmd->redirections);
	if (cmd->files)
		ft_free_strings(cmd->files);
	return (EXIT_SUCCESS);
}

int ft_free_cmd_arr(t_cmd *cmd_data, uint32_t n_cmds)
{
    uint32_t   i;

	i = 0;
	while (i < n_cmds)
	{
		ft_free_cmd_struct(cmd_data + i);
		i++;
	}
	free(cmd_data);
	return (EXIT_SUCCESS);
}

int	ft_free_env_list(t_var *mini)
{
	t_env	*tmp;
	t_env	**env_list;

	env_list = mini->env_list;
	if (!env_list)
		return (EXIT_SUCCESS);
	while (*env_list != NULL)
	{
		tmp = *env_list;
		*env_list = (*env_list)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(env_list);
	return (EXIT_SUCCESS);
}
