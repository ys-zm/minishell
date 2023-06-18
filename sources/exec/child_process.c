#include "minishell.h"

void	ft_increment_shlvl(t_var *mini)
{
	t_env	*env_list;
	int		value;

	env_list = *(mini->env_list);
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, "SHLVL"))
			break ;
		env_list = env_list->next;
	}
	if (env_list)
	{
		value = ft_atoi(env_list->value);
		value += 1;
		free(env_list);
		env_list->value = ft_itoa(value);
	}
}

void	ft_set_shlvl(t_var *mini, char *cmd_name)
{
	if (!ft_strcmp("./minishell", cmd_name))
	{
		if (ft_check_if_key_exists(*(mini->env_list), "SHLVL"))
			ft_increment_shlvl(mini);
		else
			ft_add_node(mini->env_list, ft_new_node("SHLVL", "1"));
	}
}

// Execution of single command using execve(). Global variable g_exit_code is set to 0. 
// If it fails, g_exit_code is switched to 127 with ft_error_msg() function.
int	ft_exec_child_single(t_var *mini)
{
	char	*cmd_path;
	t_cmd	cmd;

	cmd_path = NULL;
	cmd = mini->cmd_data[0];
	if (!cmd.cmd_name)
		exit(EXIT_SUCCESS);
	cmd_path = access_cmd_path(mini, cmd.cmd_name);
	ft_set_shlvl(mini, cmd.cmd_name);
	g_exit_code = 0;
	mini->env_arr = ft_list_to_arr(mini, *(mini->env_list));
	execve(cmd_path, cmd.full_cmd, mini->env_arr);
	free(cmd_path);
	ft_error_msg(mini, cmd.cmd_name, 127);
	ft_free_all(mini);	
	exit(g_exit_code); //not sure if I should exit here
}

int	ft_exec_child_multiple(t_var *mini, int index)
{
	char    *cmd_path;
	t_cmd   cmd;
	int	status_check;

	status_check = 0;
	cmd_path = NULL;
	cmd = mini->cmd_data[index];
	if (!cmd.cmd_name)
		exit(EXIT_SUCCESS);
	if (!ft_if_builtin(cmd.cmd_name))
	{
		write(STDERR_FILENO, "hi\n", 3);
		cmd_path = access_cmd_path(mini, cmd.cmd_name);
		g_exit_code = 0;
		execve(cmd_path, cmd.full_cmd, mini->env_arr);
		free(cmd_path);
		g_exit_code = 127;
	}
	else
	{
		write(STDERR_FILENO, "h2\n", 3);	
		g_exit_code = 0;
		printf("hoi\n");
		char x = cmd.fd_out + 48;
		 write(STDERR_FILENO, &x, 1);
		 write(STDERR_FILENO, "\n", 1);
		status_check = ft_exec_builtin(mini, index, cmd.fd_out);
		char c = status_check + 48;
		write(STDERR_FILENO, &c, 1);
		write(STDERR_FILENO, "\n", 1);
		if (status_check)
			g_exit_code = status_check;
		else
			exit(status_check);
	}
	printf("hi!\n");
	ft_error_msg(mini, cmd.cmd_name, g_exit_code);
	ft_free_all(mini);
	exit(g_exit_code);
}


void ft_exec_multiple(t_var *mini, u_int32_t index)
{
    if (index > 0)
    {
		printf("fd_in : %d\n", mini->cmd_data->fd_in);
		dup2(mini->pipes[index - 1][READ], STDIN_FILENO);
	}
	
    if (index < mini->n_cmd - 1)
    {
		printf("fd_out : %d\n", mini->cmd_data->fd_out);
		dup2(mini->pipes[index][WRITE], STDOUT_FILENO);
	}
	if (ft_if_redir(mini, index))
    {
		printf("shouldnt print this\n");
		ft_redirect(mini, index);
	}
    close_pipes(mini);
    ft_exec_child_multiple(mini, index);
}
