/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:46:55 by fra           #+#    #+#                 */
/*   Updated: 2023/06/12 16:59:32 by yzaim         ########   odam.nl         */
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
	char 		start_quote;
	char 		*eof;
	uint32_t	i;

	i = 0;
	if (is_quote(*start))
	{
		start_quote = *start;
		while (*start && (*start == start_quote))
			start++;
		while (start[i] && (start[i] != start_quote))
			i++;
	}	
	else
	{
		while (start[i] && (! ft_isspace(start[i])) && (! is_arrow(start[i])) && (start[i] != '|'))
			i++;
	}
	eof = ft_calloc((i + 1), sizeof(char));
	if (eof)
	{
		while (i--)
			eof[i] = start[i];
	}
	return (eof);
}

t_cmd_status	read_stdin(char *eof, char **here_doc)
{
	char			*new_line;
	t_cmd_status	status;
	
	while (true)
	{
		status = ft_readline(&new_line, "> ", false);
		if ((status == CMD_MEM_ERR) || (status == CMD_NULL_ERR))
		{
			ft_free(*here_doc);
			return (status);
		}
		else if (ft_strncmp(new_line, eof, ft_strlen(eof)) == 0)
		{
			ft_free(new_line);
			return (CMD_OK);
		}
		*here_doc = ft_strjoin(*here_doc, new_line, "\n", true);
		if (*here_doc == NULL)
			return (CMD_MEM_ERR);
	}
}

char	*create_file_name(int32_t cnt)
{
	char			*file_name;
	char			*char_cnt;

	char_cnt = ft_itoa(cnt);
	if (char_cnt == NULL)
		return (NULL);
	file_name = ft_strjoin("here_doc/here_doc", char_cnt, "_", false);
	ft_free(char_cnt);
	return (file_name);
}

t_cmd_status	write_here_doc(char *file_name, char *delimiter)
{
	t_cmd_status	status;
	char			*here_doc;
	int32_t			fd;

	here_doc = NULL;
	status = read_stdin(delimiter, &here_doc);
	if ((status == CMD_MEM_ERR) || (status == CMD_NULL_ERR))
		exit(status);
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if ((fd == -1) || (write(fd, here_doc, ft_strlen(here_doc)) == -1))
		status = CMD_MEM_ERR;
	close(fd);
	ft_free(here_doc);
	exit(status);
}

int32_t	fork_here_doc(char *file_name, char *delimiter)
{
	pid_t	child_id;
	int32_t	status_procs;

	child_id = fork();
	if (child_id == -1)
		return (-1);
	else if (child_id == 0)
		write_here_doc(file_name, delimiter);
	else
	{
		if (waitpid(child_id, &status_procs, 0) == -1)
			return (-1);
		if (WIFEXITED(status_procs))
		{
			if (WEXITSTATUS(status_procs) == CMD_MEM_ERR)
				return (-1);
		}
	}
	return (0);
}

int32_t	handle_here_doc(char **cmd, uint32_t *cnt)
{
	char	*delimiter;
	int32_t	del_pos;
	int32_t	status_fork;
	char	*file_name;

	del_pos = find_next_eof_pos(*cmd, 0);
	while (del_pos != -1)
	{
		if (get_order_cmd(*cmd, del_pos) >= *cnt)
			*cnt = get_order_cmd(*cmd, del_pos);
		else
			*cnt += get_order_cmd(*cmd, del_pos);
		file_name = create_file_name(*cnt);
		if (file_name == NULL)
			return (-1);
		delimiter = isolate_eof(*cmd + del_pos);
		if (delimiter == NULL)
		{
			ft_free(file_name);
			return (-1);
		}
		status_fork = fork_here_doc(file_name, delimiter);
		ft_free(delimiter);
		ft_free(file_name);
		if (status_fork == -1)
			return (-1);
		del_pos = find_next_eof_pos(*cmd, del_pos);
	}
	*cnt += find_next_eof_pos(*cmd, 0) != -1;
	return (0);
}

