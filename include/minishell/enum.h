/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enum.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 01:56:43 by fra           #+#    #+#                 */
/*   Updated: 2023/07/07 15:54:01 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum s_cmd_status
{
	CMD_OK,
	CMD_CTRL_C,
	CMD_CTRL_D,
	CMD_MEM_ERR,
	CMD_SIN_ERR,
	CMD_FILE_ERR,
	CMD_PROC_ERR,
}	t_cmd_status;

typedef enum s_red_type
{
	RED_IN_SINGLE,	
	RED_OUT_SINGLE,
	RED_IN_DOUBLE,
	RED_OUT_DOUBLE,
}	t_red_type;

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
}	t_env;

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
	t_cmd		*cmd_data;
	uint32_t	n_cmd;
	t_env		**env_list;
	char		**env_arr;
	char		**paths;
	int			**pipes;
	pid_t		*pid;
	int			status;
	char		*shell_loc;
	char		*here
}	t_var;

#endif

