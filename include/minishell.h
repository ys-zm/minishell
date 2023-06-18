/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/17 22:02:45 by fra           #+#    #+#                 */
/*   Updated: 2023/06/18 00:07:37 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ				0
# define WRITE				1
# define REPLACE			2
# define APPEND				3
# define RED   				"\x1B[31m"	// colors for the messages on the stdout
# define GRN   				"\x1B[32m"
# define YEL   				"\x1B[33m"
# define BLU   				"\x1B[34m"
# define MAG   				"\x1B[35m"
# define COL_RESET 			"\x1B[0m"
# define BOLD				"\033[1m"
# define BOLD_RESET			"\033[0m"
# define HERE_DOC_FIX		"here_doc/here_doc"
# define PROMPT				BOLD YEL "MI" MAG "NI" RED "HELL-> "  COL_RESET BOLD_RESET
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>    	// malloc(), free()
# include <unistd.h>    	// write(), read(), ...
 # include <fcntl.h>			// macro to open files (O_CREAT, O_WRONLY, O_RDONLY ..)
# include <stdbool.h>		// boolean types
# include <stdint.h>		// cross-compiler types
# include <signal.h>    	// signal(), sigemptyset(), kill(), getpid(), ...
# include <termios.h>		// terminal configuration stuff
# include <sys/wait.h>
# include <errno.h>
# include <stddef.h>
# include <limits.h>
# include <dirent.h>

extern int g_exit_code;

typedef struct termios t_termios;

typedef enum s_cmd_status
{
	CMD_OK,
	CMD_SIN_ERR,
	CMD_MEM_ERR,
	CMD_PROC_ERR,
	CMD_EOF,
	CMD_EMPTY,
}	t_cmd_status;

typedef enum s_hd_status
{
	HD_OK,
	HD_EOF,
	HD_MEM_ERR,
	HD_FILE_ERR,
}	t_hd_status;

typedef enum s_red_type
{
	RED_IN_SINGLE,		// <
	RED_OUT_SINGLE,		// >
	RED_IN_DOUBLE,		// <<
	RED_OUT_DOUBLE,		// >>
	RED_ERROR,
}	t_red_type;

typedef struct s_env	{
    struct s_env    *next;
    char            *key;
    char            *value;
}   t_env;

typedef struct s_cmd
{
	char				*cmd_name;
	char				**full_cmd;
	uint32_t			n_redirect;
	t_red_type			*redirections;
	char				**files;
	int32_t				fd_in;
	int32_t				fd_out;
}	t_cmd;

typedef struct s_var
{
    t_cmd       *cmd_data;
    uint32_t   n_cmd;
    t_env       **env_list;
    char        **env_arr;
    char        **paths;
    int         **pipes;
    pid_t       *pid;
    int         status;
}   t_var;


void    ft_print_array(char **arr);

//Free Functions for Data Types --> error_handling/free.c
int ft_free_strings(char **arr);
int ft_free_pipes(int **pipes, int size);
int ft_free_cmd_struct(t_cmd *cmd);
int ft_free_cmd_arr(t_cmd *cmd_data, u_int32_t n_cmds);
int ft_free_env_list(t_env **env_list);
void    ft_free_and_null(void *var);
//Error Handling Functions --> error_handling/error.c

void	ft_free_all(t_var *mini);
void	ft_error_msg(t_var *mini, char *str, int error);
int	malloc_protect(t_var *mini);

// Util Functions --> builtins/utils.c
int	    ft_strcmp(const char *s1, const char *s2);
char    *ft_trip_join(char *str1, char *str2, char *str3);
size_t  count_args(char **args);

//Builtin Functions --> builtins/ft_funcname.c
int     ft_pwd(int fd_out);
int     ft_cd(t_var *mini, char **args, int fd_out);
int     ft_env(t_var *mini, int fd_out);
int		ft_echo(char **args, int fd_out);
int    ft_unset(t_var *mini, char **args, int fd_out);
int		ft_exit(t_var *mini, char **args, int fd_out);
int		ft_export(t_var *mini, char **args, int fd_out);

char    **ft_list_to_arr(t_var *mini, t_env *env_list);
void	ft_add_node(t_env **env_list, t_env *new_node);
//Export Utils
int 	ft_find_operator_type(char *env);
int 	ft_find_operator_pos(char *env);
int 	ft_check_if_same_value(t_env *env_list, char *key, char *value);
int 	ft_check_if_key_exists(t_env *env_list, char *key);
int 	ft_find_first_equals(char *env);
int		ft_check_key(char *key);
void    ft_redir_type(t_var *mini, int index);
void    ft_replace_value(t_var *mini, char *key, char *new_value);
void    ft_append_value(t_var *mini, char *key, char *to_add);
void    make_env_list(char **envp, t_var *mini);

char	*ft_find_value(t_var *mini, char *arg, size_t op_type, size_t op_pos);

t_env	*ft_new_node(char *key, char *value);

// Functions for ENV Parsing and Export Function
t_env   *ft_envp_node(t_var *mini, char *envp);

void    ft_exec(t_var *mini);
void    ft_command_not_found(t_var *mini, char *cmd);
void    ft_permission_denied(t_var *mini, char *cmd);

//Main functions

int		set_up_struct(t_var **mini, char **envp);

void    fill_up_struct(t_var *mini);

// Exec Functions

void    ft_mem_alloc(t_var *mini);

bool    ft_if_builtin(char *func);

bool    ft_if_redir(t_var *mini, int index);

bool    ft_check_permission(t_cmd *cmd, t_red_type red_type, int index);

int    ft_exec_builtin(t_var *mini, int index, int fd_out);

//Functinons to check if program exists in paths --> exec/access.c
char    *check_env_paths(t_var *mini, char *cmd);

char    *check_cwd(t_var *mini, char *cmd);

bool    check_absolute_path(char *cmd);

char    *access_cmd_path(t_var *mini, char *cmd);

void    create_pipes(t_var *mini);

void    ft_exec_multiple(t_var *mini, u_int32_t index);

void    close_pipes(t_var *mini);

void	ft_redirect(t_var *mini, int index);

int	wait_for_children(t_var *mini);

int	ft_exec_child_single(t_var *mini);

char    *ft_find_path(t_var *mini);

void    ft_split_path(t_var *mini);

int		process_management(t_var *mini);

//==============================================================

bool			check_quotes(char *cmd);

bool    		check_pipes(char *cmd);

bool    		check_redirections(char *str);

bool			check_sintax(char *cmd);


bool 			is_valid_char(char *string, uint32_t pos_to_check, char check);

bool			is_valid_space(char *string, uint32_t pos_to_check);

bool 			is_valid_arrow(char *string, uint32_t pos_to_check);

bool			is_valid_dollar(char *string, uint32_t pos_to_check);

bool 			is_valid_quote(char *string, uint32_t pos_to_check);


uint32_t		n_cmds(char *string);

char			**split_into_cmds(char *input_cmd);

uint32_t		count_words(t_list *tokens);

uint32_t		count_redirections(t_list *tokens);

// bool			has_redirections(t_list *tokens);

bool			get_cmd(t_list *tokens, t_cmd *cmd);

bool			get_redirections(t_list *tokens, t_cmd *cmd, int32_t order_cmd);

bool			is_redirection(char	*word);

bool			split_input(t_cmd *cmd, t_list *tokens, int32_t order_cmd);

t_red_type		get_type_redirection(char *to_check);

t_list			*tokenize(char *input);


char			*expand_vars(char *input, t_env *env_vars);

char			*get_var_value(t_env *env_vars, char *var_name);


t_cmd_status	ft_readline(char **buffer, const char *prompt, bool check);

t_cmd_status	aquire_cmd(char **cmd);

t_cmd			*create_new_cmd(char *cmd, t_var *depo);

void    		main_loop(t_var	*main_var);


int32_t			find_next_eof_pos(char *cmd, uint32_t start_pos);

char			*isolate_eof(char *start);

int32_t			handle_here_doc(char *cmd, uint32_t *cnt);

t_cmd_status	read_stdin(char *eof, char **here_doc);

t_cmd_status	write_here_doc(int cnt, char *delimiter);

int32_t			fork_here_doc(int cnt, char *delimiter);

char			*create_file_name(const char *fix_part, int32_t cnt);


uint32_t		skip_redirect_chars(char *cmd, uint32_t pos);

bool			is_only_spaces(char	*to_check);

char			*remove_quotes(char *to_clear);

bool			has_trailing_pipe(char	*cmd);

bool			is_outside_quotes(char *string, uint32_t pos_to_check);

bool			is_quote(char to_check);

bool			is_arrow(char to_check);

void			print_cmd(t_var *depo);

uint32_t		get_order_cmd(char *str, uint32_t pos);

bool			remove_here_docs(t_var *mini);

#endif
