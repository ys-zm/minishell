/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:46:55 by fra           #+#    #+#                 */
/*   Updated: 2023/06/23 18:13:51 by faru          ########   odam.nl         */
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
		else if (is_valid_char(start, eof_len, '|'))
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
	return (remove_quotes(eof));
}

t_cmd_status	read_stdin(char *eof, char **here_doc)
{
	char			*new_line;
	t_cmd_status	status;
	
	while (true)
	{
		status = ft_readline(&new_line, "> ", false);
		if (status == CMD_MEM_ERR)
		{
			ft_free(*here_doc);
			return (status);
		}
		else if (status == CMD_EOF)
		{
			ft_free(*here_doc);
			*here_doc = ft_strdup("");
			if (*here_doc == NULL)
				return (CMD_MEM_ERR);
			else
				return (CMD_EOF);
		}
		else if (ft_strncmp(new_line, eof, ft_strlen(eof)) == 0)
		{
			ft_free(new_line);
			*here_doc = ft_append_char(*here_doc, '\n');
			if (*here_doc == NULL)
				return (CMD_MEM_ERR);
			else
				return (CMD_OK);
		}
		*here_doc = ft_strjoin(*here_doc, new_line, "\n", true);
		if (*here_doc == NULL)
			return (CMD_MEM_ERR);
	}
}

char	*create_file_name(const char *fix_part, int32_t cnt)
{
	char			*file_name;
	char			*char_cnt;

	char_cnt = ft_itoa(cnt);
	if (char_cnt == NULL)
		return (NULL);
	file_name = ft_strjoin((char *) fix_part, char_cnt, "_", false);
	ft_free(char_cnt);
	return (file_name);
}

t_cmd_status	write_here_doc(int cnt, char *delimiter)
{
	t_cmd_status	status_cmd;
	t_hd_status		status_hd;
	char			*here_doc;
	int32_t			fd;
	char			*file_name;

	here_doc = NULL;
	status_cmd = read_stdin(delimiter, &here_doc);
	if (status_cmd == CMD_MEM_ERR)
		exit(HD_MEM_ERR);
	file_name = create_file_name(HERE_DOC_FIX, cnt);
	if (file_name == NULL)
	{
		ft_free(here_doc);
		exit(HD_MEM_ERR);
	}
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
		return (-1);		// NB it's a fail but not related to memoery issues, the return value should tell that
	else if (child_id == 0)
		write_here_doc(cnt, delimiter);
	else
	{
		if (waitpid(child_id, &status_procs, 0) == -1)
			return (-1);
		if (WIFEXITED(status_procs))
		{
			if ((WEXITSTATUS(status_procs) == HD_MEM_ERR) || (WEXITSTATUS(status_procs) == HD_FILE_ERR))
				return (-1);
		}
	}
	return (0);
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
		if (status_fork == -1)
			return (-1);
		del_pos = find_next_eof_pos(cmd, del_pos);
	}
	*cnt += find_next_eof_pos(cmd, 0) != -1;
	return (0);
}

bool remove_here_docs(t_var *mini)
{
	uint32_t	i;
	uint32_t	j;
	char		*here_doc_to_drop;
	int32_t		status;

	i = 0;
	while (i < mini->n_cmd)
	{
		j = 0;
		while (j < mini->cmd_data[i].n_redirect)
		{
			ft_printf("halo1!\n");
			if (mini->cmd_data[i].redirections[j] == RED_IN_DOUBLE)
			{
				here_doc_to_drop = create_file_name(HERE_DOC_FIX, i + 1);
				if (here_doc_to_drop == NULL)
					return (false);
				status = unlink(here_doc_to_drop);
				ft_free(here_doc_to_drop);
				if (status == -1)
					return (false);
				break ;
			}
			j++;
		}
		i++;
	}
	return (true);
}
