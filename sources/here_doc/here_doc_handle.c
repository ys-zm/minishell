/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_handle.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:15:31 by faru          #+#    #+#                 */
/*   Updated: 2023/07/17 22:13:59 by fra           ########   odam.nl         */
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

char	*isolate_del(char *start)
{
	char		*del;
	uint32_t	del_len;

	del_len = 0;
	while (is_valid_space(start, del_len))
		start++;
	while (start[del_len] != '\0')
	{
		if (is_valid_space(start, del_len))
			break ;
		else if (is_valid_arrow(start, del_len))
			break ;
		else if (is_valid_symbol(start, del_len, '|'))
			break ;
		else
			del_len++;
	}
	del = ft_calloc((del_len + 1), sizeof(char));
	if (del == NULL)
		return (NULL);
	while (del_len--)
		del[del_len] = start[del_len];
	return (del);
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

t_cmd_status	handle_here_doc(char *cmd, uint32_t *cnt, t_var *mini)
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
		del = isolate_del((cmd + del_pos));
		if (del == NULL)
			return (CMD_MEM_ERR);
		status = fork_here_doc(*cnt, del, mini);
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

bool	remove_here_docs(char *here_doc_path)
{
	struct dirent	*entry;
	DIR				*dir;
	char			*file_name;
	bool			success;

	dir = opendir(here_doc_path);
	if (dir == NULL)
		return (false);
	entry = readdir(dir);
	success = true;
	while ((entry != NULL) && (success == true))
	{
		if (entry->d_type == DT_REG && \
		ft_strnstr(entry->d_name, "here_doc_", 9))
		{
			success = false;
			file_name = ft_strjoin(here_doc_path, entry->d_name, "/", false);
			if (file_name == NULL)
				return (false);
			success = unlink(file_name) == 0;
			ft_free(file_name);
		}
		entry = readdir(dir);
	}
	return (closedir(dir), success);
}
