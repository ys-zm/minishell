/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/17 22:02:45 by fra           #+#    #+#                 */
/*   Updated: 2023/09/16 23:23:34 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READ						0
# define WRITE						1
# define REPLACE					2
# define APPEND						3
# define HERE_DOC_FIX				"/here_doc_"
# define PROMPT						"minishell-> "
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <errno.h>
# include <stddef.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
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

extern int	*g_exit_code;

// debugging functions
void	ft_print_array(char **arr);

void	print_cmd(t_var	*mini);

#endif
