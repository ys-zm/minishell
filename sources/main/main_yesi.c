#include "minishell.h"

void f(void)
{
	system("leaks -q minishell");
	// system("lsof -c minishell");
}

void	signal_handler(int signum, siginfo_t *client, void *ucontext)
{
	rl_replace_line("", 0);
	signum++;
	client++;
	ucontext++;
}

int global_exit_code;

int main(int argc, char **argv, char **envp)
{
	struct sigaction	action;
	t_var               *mini;

	action.sa_flags = SA_NODEFER | SA_RESTART;
	action.sa_sigaction = &signal_handler;
	sigemptyset(&(action.sa_mask));
	// atexit(f);
	// if (sigaction(SIGINT, &action, NULL))
	// 	ft_printf("signal error!\n");
	(void)argc;
	(void)argv;
	set_up_struct(&mini, envp);
	main_loop(mini);
	ft_free_all(mini);
	return (EXIT_SUCCESS);
}