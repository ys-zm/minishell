/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:16:54 by fra           #+#    #+#                 */
/*   Updated: 2023/07/12 16:13:24 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//Builtin Functions and Utils including: cd, pwd, env, echo, exit, export,unset
// Cd
// ft_cd.c
int		ft_run_chdir(t_var *mini, char *arg);

int		ft_cd(t_var *mini, char **args);

// cd_utils_1.c

int		ft_cd_to_homedir(t_var *mini, char *cwd);

int		ft_cd_to_oldpwd(t_var *mini, char *cwd);

t_env	*ft_search_env_var(t_env **env_list, char *which_env);

void	ft_update_env_var(t_var *mini, t_env **env_list, \
			char *which_env, char *new_env);

char	*ft_find_env_val(t_env **env_list, char *env_var);

// Pwd 
// ft_pwd.c
char	*ft_get_pwd(t_var *mini);

int		ft_pwd(t_var *mini, char **args, int fd_out);

// Env
// ft_env.c
void	ft_print_env(char **arr, int fd_out);

size_t	ft_list_size_to_print(t_env *env_list);

char	**ft_list_to_arr(t_var *mini, t_env *env_list);

int		ft_env(t_var *mini, char **args, int fd_out);

//Echo
//ft_echo.c
t_env	*ft_find_node(t_env *env_list, char *key);

void	ft_print_echo(char **args, int i, int fd_out);

int		ft_echo(char **args, int fd_out);

// Exit
// ft_exit.c
int		ft_ifnum(char *str);

int		ft_if_sign(char *str);

bool	ft_check_atoll(char *arg);

bool	ft_check_if_numeric(char *arg);

int		ft_exit(t_var *mini, char **args);

//Export
// export_utils_1.c
int		ft_same(t_env *env_list, char *key, char *value);

int		ft_check_if_key_exists(t_env *env_list, char *key);

void	ft_replace_value(t_var *mini, char *key, char *new_value);

void	ft_append_value(t_var *mini, char *key, char *to_add);

char	*ft_find_value(t_var *mini, char *arg, size_t op_type, size_t op_pos);

// export_utils_2.c
int		ft_find_operator_pos(char *env);

int		ft_find_operator_type(char *env);

void	ft_print_export(t_env **env_list);

// ft_export.c
t_env	*ft_new_node(char *key, char *value);

void	ft_add_node(t_env **env_list, t_env *new_node);

void	ft_update_env_list(t_var *mini, char *key, char *value, size_t op_type);

int		ft_export_single(t_var *mini, char *arg, size_t op_type, size_t op_pos);

int		ft_export(t_var *mini, char **args);

// Unset
// ft_unset.c
void	ft_del_node(t_env **env_list, char *key);

int		ft_unset(t_var *mini, char **args);

// Utils
// utils.c
int		ft_strcmp(const char *s1, const char *s2);

char	*ft_trip_join(char *str1, char *str2, char *str3);

size_t	count_args(char **args);

#endif
