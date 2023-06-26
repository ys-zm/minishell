/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_handle.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:15:31 by faru          #+#    #+#                 */
/*   Updated: 2023/06/26 15:58:50 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_cmd_status	eof_here_doc(char **here_doc, t_cmd_status status)
{
	ft_free(*here_doc);
	*here_doc = ft_strdup("");
	if (*here_doc == NULL)
		status = CMD_MEM_ERR;
	return (status);
}

t_cmd_status	aquire_input_hd(char *eof, char **here_doc)
{
	char			*new_line;
	t_cmd_status	status;

	while (true)
	{
		status = ft_readline(&new_line, "> ", false);
		if (status == CMD_MEM_ERR)
			return (ft_free(*here_doc), status);
		else if (status == CMD_EOF)
			return (eof_here_doc(here_doc, status));
		else if (ft_strncmp(new_line, eof, ft_strlen(eof)) == 0)
		{
			ft_free(new_line);
			*here_doc = ft_append_char(*here_doc, '\n');
			if (*here_doc == NULL)
				status = CMD_MEM_ERR;
			return (status);
		}
		*here_doc = ft_strjoin(*here_doc, new_line, "\n", true);
		if (*here_doc == NULL)
			return (CMD_MEM_ERR);
	}
}
