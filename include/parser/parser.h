/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:06:12 by fra           #+#    #+#                 */
/*   Updated: 2023/07/01 02:44:46 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell/minishell.h"

// command.c
uint32_t		n_cmds(char *string);

char			**split_into_cmds(char *input_cmd);

t_cmd			*create_new_cmd(char *cmd, t_var *depo);

// expander.c
char			*expand_vars(char *input, t_env *env_vars);

char			*get_var_value(t_env *env_vars, char *var_name);

char			*expand_tilde(char *input, t_env *env_vars);

char			*expand_pid(char *input);

char			*expander(char *input, t_env *env_vars);

// parser.c
t_cmd_status	ft_readline(char **buffer, const char *prompt, bool check);

t_cmd_status	input_error(char **input, char *buffer, t_cmd_status status);

t_cmd_status	aquire_input(char **cmd, t_env *vars);

#endif