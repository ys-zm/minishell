/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:46:55 by fra           #+#    #+#                 */
/*   Updated: 2023/06/25 02:04:27 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_status	write_here_doc(int cnt, char *delimiter)
{
	t_cmd_status	status_cmd;
	t_hd_status		status_hd;
	char			*here_doc;
	char			*file_name;
	int32_t			fd;

	here_doc = NULL;
	status_cmd = aquire_input_hd(delimiter, &here_doc);
	if (status_cmd == CMD_MEM_ERR)
		exit(HD_MEM_ERR);
	file_name = create_file_name(HERE_DOC_FIX, cnt);
	if (file_name == NULL)
		exit(HD_MEM_ERR);
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_free(file_name);
	if ((fd == -1) || (write(fd, here_doc, ft_strlen(here_doc)) == -1))
		status_hd = HD_FILE_ERR;
	else if (status_cmd == CMD_EOF)
		status_hd = HD_EOF;
	else
		status_hd = HD_OK;
	if (fd != -1)
		close(fd);
	ft_free(here_doc);
	exit(status_hd);
}

int32_t	fork_here_doc(int cnt, char *delimiter)
{
	pid_t	child_id;
	int32_t	status_procs;

	child_id = fork();
	if (child_id == -1)
		return (-2);
	else if (child_id == 0)
		write_here_doc(cnt, delimiter);
	else
	{
		if (waitpid(child_id, &status_procs, 0) == -1)
			return (-2);
		if (WIFEXITED(status_procs))
		{
			if ((WEXITSTATUS(status_procs) == HD_MEM_ERR) || (WEXITSTATUS(status_procs) == HD_FILE_ERR))
				return (-1);
		}
	}
	return (0);
}

int32_t	find_next_eof_pos(char *cmd, uint32_t start_pos)
{
	while (cmd && cmd[start_pos])
	{
		if ((cmd[start_pos] == '<') && is_outside_quotes(cmd, start_pos))
		{
			start_pos++;
			if (cmd[start_pos] == '<')
			{
				start_pos++;
				while (ft_isspace(cmd[start_pos]))
					start_pos++;
				return (start_pos);
			}
		}
		else
			start_pos++;
	}
	return (-1);
}

char	*isolate_eof(char *start)
{
	char 		*eof;
	uint32_t	eof_len;

	eof_len = 0;
	while (is_valid_space(start, eof_len))
		start++;
	while (start[eof_len] != '\0')
	{
		if (is_valid_space(start, eof_len))
			break ;
		else if (is_valid_arrow(start, eof_len))
			break ;
		else if (is_valid_symbol(start, eof_len, '|'))
			break ;
		else if (is_valid_space(start, eof_len))
			break ;
		else
			eof_len++;
	}
	eof = ft_calloc((eof_len + 1), sizeof(char));
	if (eof == NULL)
		return (NULL);
	while (eof_len--)
		eof[eof_len] = start[eof_len];
	return (remove_quotes(eof, true));
}

uint32_t	get_order_cmd(char *str, uint32_t pos)
{
	uint32_t	order;
	char		*next_pipe;
	uint32_t	pipe_pos;

	order = 1;
	pipe_pos = 0;
	while (true)
	{
		while (true)
		{
			next_pipe = ft_strchr(str + pipe_pos, '|');
			if (next_pipe == NULL)
				return (order);
			pipe_pos = next_pipe - str;
			if (is_valid_symbol(str, pipe_pos, '|'))
				break ;
		}
		if (pos > pipe_pos)
		{
			order++;
			pipe_pos++;
		}
		else
			break ;
	}
	return (order); 
}

int32_t	handle_here_doc(char *cmd, uint32_t *cnt)
{
	char	*delimiter;
	int32_t	del_pos;
	int32_t	status_fork;

	del_pos = find_next_eof_pos(cmd, 0);
	while (del_pos != -1)
	{
		if (get_order_cmd(cmd, del_pos) >= *cnt)
			*cnt = get_order_cmd(cmd, del_pos);
		else
			*cnt += get_order_cmd(cmd, del_pos);
		delimiter = isolate_eof((cmd + del_pos));
		if (delimiter == NULL)
			return (-1);
		status_fork = fork_here_doc(*cnt, delimiter);
		ft_free(delimiter);
		if (status_fork != 0)
			return (status_fork);
		del_pos = find_next_eof_pos(cmd, del_pos);
	}
	*cnt += find_next_eof_pos(cmd, 0) != -1;
	return (0);
}
