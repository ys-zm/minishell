/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_fra.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 02:32:32 by fra           #+#    #+#                 */
/*   Updated: 2023/06/11 18:37:14 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void f(void)
{
	system("leaks -q minishell");
}

void	signal_handler(int signum, siginfo_t *client, void *ucontext)
{
	rl_replace_line("", 0);
	signum++;
	client++;
	ucontext++;
}

int main(int argc, char **argv, char **envp)
{
	struct sigaction	action;
	t_var               *mini;

	action.sa_flags = SA_NODEFER | SA_RESTART;
	action.sa_sigaction = &signal_handler;
	sigemptyset(&(action.sa_mask));
	// if (sigaction(SIGINT, &action, NULL))
	// 	ft_printf("signal error!\n");
	(void)argc;
	(void)argv;
	// atexit(f);
	set_up_struct(&mini, envp);
	main_loop(mini);
	ft_free_all(mini);
	return (EXIT_SUCCESS);
}