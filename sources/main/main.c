/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 02:32:32 by fra           #+#    #+#                 */
/*   Updated: 2023/07/16 20:35:43 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

int	g_exit_code;

void	exit_shell(char *input)
{
	if (has_trailing_pipe(input) == true)
		ft_putstr_fd("minishell: syntax error\n", 2);
	else
		ft_putstr_fd("minishell: exit\n", 2);
	ft_free(input);
}

void	run_cmd(char *input, t_var *mini)
{
	mini->cmd_data = create_new_cmd(input, mini);
	if (mini->cmd_data == NULL)
		malloc_protect(mini);
	// print_cmd(mini);
	ft_exec(mini);
}

void	main_loop(t_var *mini)
{
	t_cmd_status	status;
	char			*input;

	while (true)
	{
		input = NULL;
		status = aquire_input(&input, mini);
		if ((status == CMD_MEM_ERR) || (status == CMD_FILE_ERR)
			|| (status == CMD_PROC_ERR))
			malloc_protect(mini);
		else if (status == CMD_CTRL_D)
		{
			exit_shell(input);
			break ;
		}
		if (ft_is_empty_str(input) == false)
			add_history(input);
		if (status == CMD_OK)
			run_cmd(input, mini);
		else
			ft_free(input);
		if (status == CMD_SIN_ERR)
			ft_putstr_fd("minishell: syntax error\n", 2);
	}
	clear_history();
}

void	print_cmd(t_var	*mini)
{
	uint32_t	i;
	uint32_t	j;

	j = 0;
	if (mini == NULL)
		return;
	while (j < mini->n_cmd)
	{
		ft_printf("COMMAND\n\tcmd name: %s\n", mini->cmd_data[j].cmd_name);
		i = 0;
		while (mini->cmd_data[j].full_cmd && mini->cmd_data[j].full_cmd[i])
			ft_printf("\t\targ: %s\n", mini->cmd_data[j].full_cmd[i++]);
		if (mini->cmd_data[j].redirections)
		{
			// ft_printf("\tn. redirections: %u\n", mini->cmd_data[j].n_redirect);
			i = 0;
			while (i < mini->cmd_data[j].n_redirect)
			{
				if (mini->cmd_data[j].redirections[i] == RED_IN_SINGLE)
					ft_printf("\t\tred type: %s file: %s\n", "<", mini->cmd_data[j].files[i]);
				else if (mini->cmd_data[j].redirections[i] == RED_OUT_SINGLE)
					ft_printf("\t\tred type: %s file: %s\n", ">", mini->cmd_data[j].files[i]);
				else if (mini->cmd_data[j].redirections[i] == RED_IN_DOUBLE)
					ft_printf("\t\tred type: %s file: %s\n", "<<", mini->cmd_data[j].files[i]);
				else if (mini->cmd_data[j].redirections[i] == RED_OUT_DOUBLE)
					ft_printf("\t\tred type: %s file: %s\n", ">>", mini->cmd_data[j].files[i]);
				i++;
			}
		}
		j++;
	}
}

void	set_up_struct(t_var **mini, char **envp)
{
	char	*cwd = NULL;

	*mini = ft_calloc(1, sizeof(t_var));
	if (*mini == NULL)
		malloc_protect(*mini);
	(*mini)->cmd_data = NULL;
	(*mini)->n_cmd = 0;
	(*mini)->env_list = NULL;
	(*mini)->env_arr = NULL;
	(*mini)->paths = NULL;
	(*mini)->pipes = NULL;
	(*mini)->pid = NULL;
	make_env_list(envp, *mini);
	if ((*mini)->env_list && envp)
		cwd = get_var_value((*mini)->env_list, "SHELL");
	else
		cwd = getcwd(0, 0);
	if (cwd == NULL)
		malloc_protect(*mini);
	(*mini)->here_doc_path = ft_strjoin(cwd, HERE_DOC_FOLDER, "/", false);
	ft_free(cwd);
	if ((*mini)->here_doc_path == NULL)
		malloc_protect(*mini);
}

void	f(void)
{
	// system("leaks -q minishell");
	// system("lsof -c minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*mini;

	// atexit(&f);
	init_sig_handle(0);
	(void)argc;
	(void)argv;
	set_up_struct(&mini, envp);
	ft_set_shlvl(mini);
	main_loop(mini);
	ft_free_exec_alloc(mini);
	ft_free_all(mini);
	return (g_exit_code);
}
