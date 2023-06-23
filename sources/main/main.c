/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 02:32:32 by fra           #+#    #+#                 */
/*   Updated: 2023/06/23 13:42:52 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code;

void f(void)
{
	system("leaks -q minishell");
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// return (NULL);
}

void	init_sig_handle(int mode)
{
	if (mode == 0)		// main process
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

int main(int argc, char **argv, char **envp)
{
	// struct sigaction	action;
	t_var               *mini;
    // t_termios			term;
	
	// if (tcgetattr(STDIN_FILENO, &term) == -1)
	// {
    //     perror("tcgetattr");
    //     exit(1);
    // }
    // Imposta il flag ISIG su 0 per evitare la stampa di "^C"
    // term.c_lflag &= ~ISIG;
	// term.c_lflag &= ~ECHOCTL;
    // if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	// {
    //     perror("tcsetattr");
    //     exit(1);
    // }
	init_sig_handle(0);
	// action.sa_flags = SA_NODEFER | SA_RESTART;
	// action.sa_sigaction = &signal_handler;
	// sigemptyset(&(action.sa_mask));
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
