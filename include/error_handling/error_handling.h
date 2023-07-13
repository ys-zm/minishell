/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:17:37 by fra           #+#    #+#                 */
/*   Updated: 2023/07/13 16:30:31 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H

//Free Functions for Data Types --> error_handling/free.c
int		ft_free_strings(char **arr);

int		ft_free_pipes(int **pipes, int size);

int		ft_free_cmd_struct(t_cmd *cmd);

int		ft_free_cmd_arr(t_cmd *cmd_data, u_int32_t n_cmds);

int		ft_free_env_list(t_var *mini);

//Error Handling Functions --> error_handling/error.c
void	ft_set_to_null(t_var *mini);

void	ft_free_all(t_var *mini);

void	ft_error_msg(char *str);

int		malloc_protect(t_var *mini);

void	ft_write_error(int fd, char *func, char *str, char *msg);

#endif