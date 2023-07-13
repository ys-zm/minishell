/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:18:00 by fra           #+#    #+#                 */
/*   Updated: 2023/07/13 18:44:32 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// access_utils.c
void	ft_call_error(t_var *mini, char *cmd, char *cmd_path, int found);

bool	ft_is_path(char *cmd);

bool	ft_if_path_exists(t_var *mini);

// access.c
void	ft_find_error(t_var *mini, char *cmd);

char	*check_env_paths(t_var *mini, char *cmd);

char	*check_cwd(t_var *mini, char *cmd);

char	*find_cmd_path(t_var *mini, char *cmd);

char	*access_cmd_path(t_var *mini, char *cmd);

// builtin_exec.c
bool	ft_if_builtin(char *func);

int		ft_exec_builtin(t_var *mini, int index, int fd_out);

// child_process.c
int		ft_exec_child_single(t_var *mini);

void	ft_call_execve(t_var *mini, t_cmd cmd);

void	ft_exec_multiple(t_var *mini, u_int32_t index, int fd_in);

// exec.c
int		ft_exec_child_multiple(t_var *mini, int index);

int		single_cmd(t_var *mini);

int		multiple_cmds(t_var *mini);

void	ft_exec(t_var *mini);

// init_exec.c
void	ft_mem_alloc(t_var *mini);

void	ft_free_exec_alloc(t_var *mini);

// init_paths.c
char	*ft_find_path(t_var *mini);

void	ft_split_path(t_var *mini);

// path_utils.c
void	ft_command_not_found(t_var *mini, char *cmd);

void	ft_permission_denied(t_var *mini, char *cmd);

// redirections.c
bool	ft_if_redir(t_var *mini, int index);

bool	ft_check_permission(t_cmd *cmd, t_red_type red_type, int index);

int		ft_redir_type(t_var *mini, int index);

int		ft_file_redirect(t_var *mini, int index);

// shlvl.c
void	ft_set_shlvl(t_var *mini);

void	ft_increment_shlvl(t_var *mini);

bool	ft_check_if_minishell(t_var *mini, char *cmd_name);

#endif