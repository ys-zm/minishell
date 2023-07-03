/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/17 22:02:45 by fra           #+#    #+#                 */
/*   Updated: 2023/07/01 19:34:40 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READ						0
# define WRITE						1
# define REPLACE					2
# define APPEND						3
# define HERE_DOC_FOLDER			"here_doc/"
# define HERE_DOC_FIX				"here_doc/here_doc"
# define PROMPT						"minishell-> "
# include <stdlib.h>    			// malloc(), free()
# include <unistd.h>    			// write(), read(), ...
# include <fcntl.h>					// to open files (O_CREAT, O_WRONLY, O_RDONLY ..)
# include <stdbool.h>				// boolean types
# include <stdio.h>
# include <stdint.h>				// cross-compiler types
# include <signal.h>    			// signal(), sigemptyset(), kill(), getpid(), ...
# include <termios.h>				// terminal configuration stuff
# include <sys/wait.h>				// waitpip(), WIFSIGNALED, WEXITSTATUS
# include <errno.h>					// errorno global var, perror(), ...
# include <stddef.h>				// NULL, type size_t
# include <dirent.h>				// opendir(), readdir(), closedir(), struct dirent
# include <readline/readline.h>		// readline(), rl_on_new_line(), rl_replace_line(), rl_redisplay()
# include <readline/history.h>		// add_history()
# include "libft.h"
# include "minishell/enum.h"
# include "builtins/builtins.h"
# include "checker/checker.h"
# include "env/env.h"
# include "error_handling/error_handling.h"
# include "exec/exec.h"
# include "here_doc/here_doc.h"
# include "lexer/lexer.h"
# include "main/main.h"
# include "parser/parser.h"
# include "utils/utils.h"

extern int	g_exit_code;

// debugging functions
void	ft_print_array(char **arr);

void	print_cmd(t_var	*mini);

#endif
