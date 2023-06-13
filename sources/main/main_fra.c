/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_fra.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 02:32:32 by fra           #+#    #+#                 */
/*   Updated: 2023/06/13 17:19:31 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void f(void)
{
	system("leaks -q minishell");
}

void	signal_handler(int signum, siginfo_t *client, void *ucontext)
{
	if (signum == SIGINT)
	{
	// rl_on_new_line();
	rl_replace_line("", 1	);
	rl_redisplay();
	}
	// signum++;
	client++;
	ucontext++;
}

int main(int argc, char **argv, char **envp)
{
	struct sigaction	action;
	t_var               *mini;
    t_termios			term;
	
	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
        perror("tcgetattr");
        exit(1);
    }
    // Imposta il flag ISIG su 0 per evitare la stampa di "^C"
    term.c_lflag &= ~ISIG;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
        perror("tcsetattr");
        exit(1);
    }

	action.sa_flags = SA_NODEFER | SA_RESTART;
	action.sa_sigaction = &signal_handler;
	sigemptyset(&(action.sa_mask));
	if (sigaction(SIGINT, &action, NULL))
		ft_printf("signal error!\n");
	(void)argc;
	(void)argv;
	// atexit(f);
	set_up_struct(&mini, envp);
	main_loop(mini);
	ft_free_all(mini);
	return (EXIT_SUCCESS);
}
