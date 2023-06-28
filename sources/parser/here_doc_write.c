/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_write.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:46:55 by fra           #+#    #+#                 */
/*   Updated: 2023/06/28 12:51:20 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int32_t	open_and_expand(bool expand, int32_t cnt, char **here_doc, t_env *vars)
{
	int32_t	fd;
	char	*file_name;

	file_name = create_file_name(HERE_DOC_FIX, cnt);\
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd != -1)
	{
		free(*here_doc);
		if (file_name == NULL)
			exit(HD_MEM_ERR);
		else
			exit(HD_FILE_ERR);
	}
	ft_free(file_name);
	if (expand)
	{
		*here_doc = expander(*here_doc, vars);
		if (*here_doc == NULL)
		{
			close(fd);
			exit(HD_MEM_ERR);
		}
	}
	return (fd);
}

t_cmd_status	write_here_doc(int cnt, char *del, bool exp_vars, t_env *vars)
{
	t_cmd_status	status_cmd;
	t_hd_status		status_hd;
	char			*here_doc;
	int32_t			fd;

	here_doc = NULL;
	status_cmd = aquire_input_hd(del, &here_doc);
	if (status_cmd == CMD_MEM_ERR)
		exit(HD_MEM_ERR);
	fd = open_and_expand(exp_vars, cnt, &here_doc, vars);
	if (write(fd, here_doc, ft_strlen(here_doc)) == -1)
		status_hd = HD_FILE_ERR;
	else if (status_cmd == CMD_EOF)
		status_hd = HD_EOF;
	else
		status_hd = HD_OK;
	close(fd);
	ft_free(here_doc);
	exit(status_hd);
}

int32_t	fork_here_doc(int cnt, char *delimiter, bool exp_vars, t_env *vars)
{
	pid_t	child_id;
	int32_t	status_procs;

	child_id = fork();
	if (child_id == -1)
		return (-2);
	else if (child_id == 0)
		write_here_doc(cnt, delimiter, exp_vars, vars);
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
