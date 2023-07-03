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

void	ft_print_array(char **arr);

//To Remove
void	print_cmd(t_var	*mini);

//Free Functions for Data Types --> error_handling/free.c
int		ft_free_strings(char **arr);

int		ft_free_pipes(int **pipes, int size);

int		ft_free_cmd_struct(t_cmd *cmd);

int		ft_free_cmd_arr(t_cmd *cmd_data, u_int32_t n_cmds);

int		ft_free_env_list(t_var *mini);

void	ft_free_and_null(void *var);

//Error Handling Functions --> error_handling/error.c
void	ft_free_all(t_var *mini);

void	ft_error_msg(t_var *mini, char *str, int error);

int		malloc_protect(t_var *mini);

// Util Functions --> builtins/utils.c
int		ft_strcmp(const char *s1, const char *s2);

char	*ft_trip_join(char *str1, char *str2, char *str3);

size_t	count_args(char **args);

//Builtin Functions --> builtins/ft_funcname.c
int		ft_pwd(t_var *mini, char **args, int fd_out);

int		ft_cd(t_var *mini, char **args);

int		ft_env(t_var *mini, int fd_out);

int		ft_echo(char **args, int fd_out);

int		ft_unset(t_var *mini, char **args);

int		ft_exit(t_var *mini, char **args);

int		ft_export(t_var *mini, char **args);

//Cd Utils
char	*ft_remove_lastdir(t_var *mini, char *old_path);

char	*ft_get_home(t_var *mini);

t_env	*ft_search_env_var(t_env **env_list, char *which_env);

void	ft_update_env_var(t_var *mini, t_env **env_list, \
			char *which_env, char *new_env);

int		ft_cd_to_homedir(t_var *mini, char *cwd);

int		ft_cd_to_oldpwd(t_var *mini, char *cwd);

int		ft_count_directories(char *arg);

void	ft_write_error(int fd, char *func, char *str, char *msg);

//Export Utils
int		ft_find_operator_type(char *env);

int		ft_find_operator_pos(char *env);

int		ft_same(t_env *env_list, char *key, char *value);

int		ft_check_if_key_exists(t_env *env_list, char *key);

int		ft_find_first_equals(char *env);

int		ft_check_key(char *key, char *cmd);

int		ft_redir_type(t_var *mini, int index);

void	ft_replace_value(t_var *mini, char *key, char *new_value);

void	ft_append_value(t_var *mini, char *key, char *to_add);

void	make_env_list(char **envp, t_var *mini);

void	ft_print_export(t_env **env_list);

char	*ft_find_value(t_var *mini, char *arg, size_t op_type, size_t op_pos);

char	**ft_list_to_arr(t_var *mini, t_env *env_list);

void	ft_add_node(t_env **env_list, t_env *new_node);

t_env	*ft_new_node(char *key, char *value);

t_env	*ft_envp_node(t_var *mini, char *envp);

t_env	*ft_create_node(t_var *mini, char *envp, int pos);

// Exec Functions
void	ft_free_exec_alloc(t_var *mini);

bool	ft_if_path_exists(t_var *mini);

bool	ft_is_path(char *cmd);

void	ft_call_error(t_var *mini, char *cmd, char *cmd_path, int found);

void	ft_exec(t_var *mini);

void	ft_command_not_found(t_var *mini, char *cmd);

void	ft_permission_denied(t_var *mini, char *cmd);

//Main functions

int		set_up_struct(t_var **mini, char **envp);

void	fill_up_struct(t_var *mini);

//Shlvl Functions

void	ft_set_shlvl(t_var *mini, char *cmd_name);

void	ft_increment_shlvl(t_var *mini);

// Exec Functions
void	ft_mem_alloc(t_var *mini);

bool	ft_if_builtin(char *func);

bool	ft_if_redir(t_var *mini, int index);

bool	ft_check_permission(t_cmd *cmd, t_red_type red_type, int index);

int		ft_exec_builtin(t_var *mini, int index, int fd_out);

//Functinons to check if program exists in paths --> exec/access.c
char	*check_env_paths(t_var *mini, char *cmd);

char	*check_cwd(t_var *mini, char *cmd);

bool	check_absolute_path(char *cmd);

char	*access_cmd_path(t_var *mini, char *cmd);

void	create_pipes(t_var *mini);

void	ft_exec_multiple(t_var *mini, uint32_t index);

void	close_pipes(t_var *mini);

int		ft_redirect(t_var *mini, int index);

int		wait_for_children(t_var *mini);

int		ft_exec_child_single(t_var *mini);

char	*ft_find_path(t_var *mini);

void	ft_split_path(t_var *mini);

int		process_management(t_var *mini);

#endif
