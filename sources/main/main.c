/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 02:32:32 by fra           #+#    #+#                 */
/*   Updated: 2023/07/19 10:49:23 by faru          ########   odam.nl         */
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
	t_cmd_status	status;

	status = create_new_cmd(input, mini);
	if (status == CMD_SIN_ERR)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		if (remove_here_docs(mini->hd_path) == false)
			malloc_protect(mini);
		ft_free_cmd_arr(mini);
	}
	else if (status == CMD_MEM_ERR)
		malloc_protect(mini);
	else
		ft_exec(mini);
	g_exit_code = mini->status; //TAKE THIS OUT WHEN EXPANDER HAS ACCESS TO MINI->STATUS
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

void	set_up_struct(t_var **mini, char **envp)
{
	*mini = ft_calloc(1, sizeof(t_var));
	if (*mini == NULL)
		malloc_protect(*mini);
	(*mini)->cmd_data = NULL;
	(*mini)->n_cmd = 0;
	(*mini)->env_list = NULL;
	(*mini)->env_arr = NULL;
	(*mini)->paths = NULL;
	if (envp && *envp)
		make_env_list(envp, *mini);
	(*mini)->hd_path = getcwd(NULL, 0);
	if ((*mini)->hd_path == NULL)
		malloc_protect(*mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*mini;

	(void)argv;
	if (argc > 1)
		ft_putstr_fd("unnecessary argoment(s) provided\n", 2);
	init_sig_handle(0);
	set_up_struct(&mini, envp);
	ft_set_shlvl(mini);
	main_loop(mini);
	ft_free_all(mini);
	return (mini->status);
}
