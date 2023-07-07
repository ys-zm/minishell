/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:00:55 by fra           #+#    #+#                 */
/*   Updated: 2023/07/07 23:22:14 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "minishell/minishell.h"

// main.c
void	set_up_struct(t_var **mini, char **envp);

void	exit_shell(char *input);

void	run_cmd(char *input, t_var *mini);

void    main_loop(t_var	*main_var);

//signals.h
void	init_sig_handle(int mode);

void	signal_handler(int signum);

#endif
