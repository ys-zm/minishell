/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_write.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:46:55 by fra           #+#    #+#                 */
/*   Updated: 2023/09/21 12:04:39 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

t_cmd_status	del_here_doc(char **here_doc, t_cmd_status status)
{
	ft_free(*here_doc);
	*here_doc = ft_strdup("");
	if (*here_doc == NULL)
		status = CMD_MEM_ERR;
	return (status);
}

t_cmd_status	aquire_input_hd(char *del, char **here_doc)
{
	char			*new_line;
	t_cmd_status	status;

	while (true)
	{
		status = ft_readline(&new_line, "> ", false);
		if (status == CMD_MEM_ERR)
			return (ft_free(*here_doc), status);
		else if (status == CMD_CTRL_D)
			return (del_here_doc(here_doc, status));
		else if (ft_strncmp(new_line, del, ft_strlen(del)) == 0)
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

int32_t	open_and_expand(char **here_doc, int32_t cnt, bool expand, t_var *mini)
{
	int32_t	fd;
	char	*file_name;

	file_name = create_file_name(HERE_DOC_FIX, mini->hd_path, cnt);
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(*here_doc);
		if (file_name == NULL)
			exit(CMD_MEM_ERR);
		else
			exit(CMD_FILE_ERR);
	}
	ft_free(file_name);
	if (expand)
	{
		if (expander(here_doc, mini->env_list, mini->status, false) == CMD_MEM_ERR)
		{
			close(fd);
			exit(CMD_MEM_ERR);
		}
	}
	return (fd);
}

void	write_here_doc(int cnt, char *del, t_var *mini)
{
	t_cmd_status	status;
	char			*here_doc;
	bool			exp_vars;
	int32_t			fd;

	init_sig_handle(3);
	here_doc = NULL;
	exp_vars = (ft_strchr(del, '\'') == NULL) && (ft_strchr(del, '"') == NULL);
	del = remove_quotes(del, false);
	if (del == NULL)
		exit(CMD_MEM_ERR);
	status = aquire_input_hd(del, &here_doc);
	if (status == CMD_MEM_ERR)
	{
		ft_free(del);
		exit(status);
	}
	fd = open_and_expand(&here_doc, cnt, exp_vars, mini);
	if (write(fd, here_doc, ft_strlen(here_doc)) == -1)
		status = CMD_FILE_ERR;
	ft_free(del);
	close(fd);
	ft_free(here_doc);
	exit(status);
}

t_cmd_status	fork_here_doc(int cnt, char *del, t_var *mini)
{
	t_cmd_status	status;
	int32_t			status_procs;
	pid_t			child_id;

	status = CMD_OK;
	child_id = fork();
	if (child_id == -1)
		status = CMD_PROC_ERR;
	else if (child_id == 0)
		write_here_doc(cnt, del, mini);
	else
	{
		init_sig_handle(1);
		if (waitpid(child_id, &status_procs, 0) == -1)
			status = CMD_PROC_ERR;
		else if (WIFSIGNALED(status_procs))
		{
			mini->status = 1;
			status = CMD_CTRL_C;
		}
		else
			status = WEXITSTATUS(status_procs);

	}
	init_sig_handle(0);
	return (status);
}
