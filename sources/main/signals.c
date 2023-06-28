/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 11:57:18 by faru          #+#    #+#                 */
/*   Updated: 2023/06/28 15:28:27 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (mode == 1)		// block signals from parent while in fork (in main before forking)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		// g_exit_code = 128 + ;
	}
	else if (mode == 2)		// inside child (in child while forking)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
