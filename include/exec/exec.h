/* ************************************************************************** */
/*                    */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:18:00 by fra           #+#    #+#                 */
/*   Updated: 2023/07/17 13:08:44 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// access_utils.c
void			ft_call_error(t_var *mini, char *cmd, \
				char *cmd_path, int found);

bool			ft_is_path(char *cmd);

bool			ft_if_path_exists(t_var *mini);

// access.c
void			ft_find_error(t_var *mini, char *cmd);

char			*check_env_paths(t_var *mini, char *cmd);

char			*check_cwd(t_var *mini, char *cmd);

char			*find_cmd_path(t_var *mini, char *cmd);

char			*access_cmd_path(t_var *mini, char *cmd);

// builtin_exec.c
bool			ft_if_builtin(char *func);

int				ft_exec_builtin(t_var *mini, int index, int fd_out);

int				ft_run_builtin(t_var *mini);

// child_process.c
int				ft_exec_child_single(t_var *mini);

void			ft_call_execve(t_var *mini, t_cmd cmd);

int				ft_exec_child_multiple(t_var *mini, int index);

void			ft_exec_multiple(t_var *mini, u_int32_t index, int fd_in);

// ft_single.c 
int				single_cmd(t_var *mini);

// ft_multiple.c 
void			ft_close_pipe(int *pipe);

int				pipe_and_fork(t_var *mini, int fd_prev, uint32_t index);

int				ft_parent_close_fds(t_var *mini, int fd_in, u_int32_t index);

int				multiple_cmds(t_var *mini);

// exec.c
void			ft_exec(t_var *mini);

// init_exec.c
void			ft_init(t_var *mini);

void			ft_free_exec_alloc(t_var *mini);

// init_paths.c
char			*ft_find_path(t_var *mini);

void			ft_split_path(t_var *mini);

// path_utils.c
void			ft_command_not_found(t_var *mini, char *cmd);

void			ft_permission_denied(t_var *mini, char *cmd);

// redirections.c
bool			ft_if_redir(t_var *mini, int index);

bool			ft_check_permission(t_cmd *cmd, t_red_type red_type, int index);

int				ft_redir_type(t_var *mini, int index);

int				ft_file_redirect(t_var *mini, int index);

// redirections_2.c

void			ft_do_redirections(t_var *mini, int index);

int				ft_pipe_dup(int fd, int fileno);

int				redirect_pipe_in(t_var *mini, int index);

int				redirect_pipe_out(t_var *mini, int index);

// shlvl.c

int				ft_check_if_digits(char *str);

t_shlvl_status	ft_check_val_shlvl(char *val);

void			ft_change_node(t_env *env, char *new_val);

void			ft_update_shlvl(t_shlvl_status ret, t_env *env);

void			ft_add_to_env(t_var *mini, char *key, char *value);

//shlvl_2.c

void			ft_set_shlvl(t_var *mini);

#endif