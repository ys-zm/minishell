#include "minishell.h"

// free all allocated memory
void    ft_free_all(t_var *mini)
{
	if (mini->cmd_data)
	{
		ft_free_cmd_arr(mini->cmd_data, mini->n_cmd);
		mini->cmd_data = NULL;
	}
	ft_free_env_list(mini->env_list);
	if (mini->pipes)
	{	
		ft_free_pipes(mini->pipes, mini->n_cmd - 1);
		mini->pipes = NULL;	
	}	
	if (mini->paths)
	{
		ft_free_strings(mini->paths);
		mini->paths = NULL;
	}
	if (mini->env_arr)
	{
		ft_free_strings(mini->env_arr);	
		mini->env_arr = NULL;
	}
	if (mini->pid)
	{
		free(mini->pid);
		mini->pid = NULL;
	}
	free(mini);
}

// print error message from minishell and set g_exit_code
// function does not exit
void	ft_error_msg(t_var *mini, char *str, int error)
{
	(void)mini;
	ft_putstr_fd("minishell: ", 2);
	// ft_putstr_fd(str, 2);
	perror(str);
	g_exit_code = error;
}

// kill program when malloc fails, sets exit code to 1
int    malloc_protect(t_var *mini)
{
	ft_free_all(mini);
	ft_error_msg(mini, "", 1);
	exit(g_exit_code);
}
