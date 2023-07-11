/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 02:32:32 by fra           #+#    #+#                 */
/*   Updated: 2023/07/11 18:15:26 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

int	g_exit_code;

void	exit_shell(char *input)
{
	if (has_trailing_pipe(input) == true)
		ft_printf("minishell: syntax error\n");
	else
		ft_printf("minishell: exit\n");
	ft_free(input);
}

void	run_cmd(char *input, t_var *mini)
{
	mini->cmd_data = create_new_cmd(input, mini);
	if (mini->cmd_data == NULL)
		malloc_protect(mini);
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
			ft_printf("minishell: syntax error\n");
	}
	clear_history();
}

void	set_up_struct(t_var **mini, char **envp)
{
	char	*cwd;

	*mini = ft_calloc(1, sizeof(t_var));
	if (*mini == NULL)
		exit(EXIT_FAILURE);
	(*mini)->cmd_data = NULL;
	(*mini)->n_cmd = 0;
	(*mini)->env_list = NULL;
	(*mini)->env_arr = NULL;
	(*mini)->paths = NULL;
	(*mini)->pipes = NULL;
	(*mini)->pid = NULL;
	make_env_list(envp, *mini);
	cwd = get_var_value(*((*mini)->env_list), "SHELL");
	if (cwd == NULL)
		malloc_protect(*mini);
	(*mini)->here_doc_path = ft_strjoin(cwd, HERE_DOC_FOLDER, "/", false);
	ft_free(cwd);
	if ((*mini)->here_doc_path == NULL)
		malloc_protect(*mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*mini;

	init_sig_handle(0);
	(void)argc;
	(void)argv;
	set_up_struct(&mini, envp);
	ft_set_shlvl(mini);
	main_loop(mini);
	ft_free_exec_alloc(mini);
	ft_free_all(mini);
	return (EXIT_SUCCESS);
}
