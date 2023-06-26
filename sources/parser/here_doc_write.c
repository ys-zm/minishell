/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_write.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:46:55 by fra           #+#    #+#                 */
/*   Updated: 2023/06/26 15:58:44 by faru          ########   odam.nl         */
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
			if ((WEXITSTATUS(status_procs) == HD_MEM_ERR) || \
				(WEXITSTATUS(status_procs) == HD_FILE_ERR))
				return (-1);
		}
	}
	return (0);
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
