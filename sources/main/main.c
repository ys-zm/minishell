/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 02:32:32 by fra           #+#    #+#                 */
/*   Updated: 2023/06/29 11:57:41 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		status = aquire_input(&input, *mini->env_list);
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
	make_env_list(envp, *mini);
	(*mini)->env_arr = NULL;
	(*mini)->paths = NULL;
	(*mini)->pipes = NULL;
	(*mini)->pid = NULL;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*mini;

	init_sig_handle(0);
	(void)argc;
	(void)argv;
	set_up_struct(&mini, envp);
	main_loop(mini);
	ft_free_all(mini);
	return (EXIT_SUCCESS);
}
