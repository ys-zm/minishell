/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 02:32:32 by fra           #+#    #+#                 */
/*   Updated: 2023/06/26 17:00:50 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_sig_handle(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == 3)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	main_loop(t_var *mini)
{
	t_cmd_status	status;
	char			*input;

	while (true)
	{
		input = NULL;
		status = aquire_input(&input);
		if (status == CMD_MEM_ERR)
			malloc_protect(mini);
		else if (status == CMD_EOF)
		{
			exit_shell(input);
			break ;
		}
		if (is_empty(input) == false)
			add_history(input);
		if (status == CMD_SIN_ERR)
		{
			ft_printf("minishell: syntax error\n");
			ft_free(input);
		}
		else
			run_cmd(input, mini);
	}
	clear_history();
}

int	set_up_struct(t_var **mini, char **envp)
{
	*mini = ft_calloc(1, sizeof(t_var));
	if (*mini == NULL)
		return (EXIT_FAILURE);
	(*mini)->cmd_data = NULL;
	(*mini)->n_cmd = 0;
	(*mini)->env_list = NULL;
	(void)envp;
	(*mini)->shell_loc = NULL;
	make_env_list(envp, *mini);
	(*mini)->env_arr = NULL;
	(*mini)->paths = NULL;
	(*mini)->pipes = NULL;
	(*mini)->pid = NULL;
	return (EXIT_SUCCESS);
}

void	f(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*mini;

	atexit(&f);
	init_sig_handle(0);
	(void)argc;
	(void)argv;
	set_up_struct(&mini, envp);
	main_loop(mini);
	ft_free_all(mini);
	return (EXIT_SUCCESS);
}
