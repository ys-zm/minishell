#include "minishell.h"

void	ft_mem_alloc(t_var *mini)
{
	uint32_t i;

	i = 0;
	mini->cmd_data->fd_in = 0;
	mini->cmd_data->fd_out = 1;
	mini->pid = malloc(sizeof(pid_t) * mini->n_cmd);
	if (!mini->pid)
		malloc_protect(mini);
	mini->pipes = malloc(sizeof(int *) * (mini->n_cmd - 1));
	if (mini->n_cmd > 1 && !mini->pipes)
		malloc_protect(mini);
	while (mini->pipes != NULL && i < mini->n_cmd - 1)
	{
		mini->pipes[i] = malloc(sizeof(int) * 2);
		if (!mini->pipes[i])
			malloc_protect(mini);
		i++;
	}
}
