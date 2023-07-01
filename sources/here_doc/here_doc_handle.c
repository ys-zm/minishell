/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_handle.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:15:31 by faru          #+#    #+#                 */
/*   Updated: 2023/07/01 02:35:39 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

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
	char		*eof;
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
	char		*next_pipe;
	uint32_t	pipe_pos;
	uint32_t	order;

	pipe_pos = 0;
	order = 1;
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
		order += pos > pipe_pos;
		pipe_pos += pos > pipe_pos;
		if (pos <= pipe_pos)
			break ;
	}
	return (order);
}

t_cmd_status	handle_here_doc(char *cmd, uint32_t *cnt, t_env *vars)
{
	t_cmd_status	status;
	int32_t			del_pos;
	char			*del;

	status = CMD_OK;
	del_pos = find_next_eof_pos(cmd, 0);
	while (del_pos != -1)
	{
		if (get_order_cmd(cmd, del_pos) >= *cnt)
			*cnt = get_order_cmd(cmd, del_pos);
		else
			*cnt += get_order_cmd(cmd, del_pos);
		del = isolate_eof((cmd + del_pos));
		if (del == NULL)
			return (CMD_MEM_ERR);
		status = fork_here_doc(*cnt, del, ! is_quote(cmd[del_pos]), vars);
		ft_free(del);
		if ((status != CMD_OK) && (status != CMD_CTRL_D))
			break ;
		del_pos = find_next_eof_pos(cmd, del_pos);
	}
	*cnt += find_next_eof_pos(cmd, 0) != -1;
	if (status == CMD_CTRL_D)
		status = CMD_OK;
	return (status);
}

bool	remove_here_docs(void)
{
	struct dirent	*entry;
	DIR				*dir;
	char			*file_name;
	int32_t			status;
	bool			success;

	dir = opendir(HERE_DOC_FOLDER);
	if (dir == NULL)
		return (false);
	entry = readdir(dir);
	success = true;
	while ((entry != NULL) && (success == true))
	{
		if (is_actual_file(entry->d_name) == true)
		{
			success = false;
			file_name = ft_strjoin(HERE_DOC_FOLDER, entry->d_name, "", false);
			status = unlink(file_name);
			ft_free(file_name);
			success = status != -1;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (success);
}
