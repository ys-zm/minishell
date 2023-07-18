/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 21:39:02 by fra           #+#    #+#                 */
/*   Updated: 2023/07/18 22:57:52 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

uint32_t	count_words(t_list *tokens)
{
	uint32_t	cnt;
	char		*word;

	cnt = 0;
	while (tokens)
	{
		word = (char *) tokens->content;
		if (is_arrow(*word))
			tokens = tokens->next;
		else
			cnt++;
		tokens = tokens->next;
	}
	return (cnt);
}

t_cmd_status	fill_words(t_cmd *cmd, t_list *tokens)
{
	uint32_t	i;

	cmd->full_cmd = ft_calloc(cmd->n_words + 1, sizeof(char *));
	if (cmd->full_cmd == NULL)
		return (CMD_MEM_ERR);
	i = 0;
	while (tokens)
	{
		if (is_redirection(tokens))
			tokens = tokens->next;
		else
		{
			cmd->full_cmd[i] = remove_quotes(tokens->content, false);
			if (cmd->full_cmd[i] == NULL)
			{
				ft_free(cmd->full_cmd);
				return (CMD_MEM_ERR);
			}
			i++;
		}
		tokens = tokens->next;
	}
	cmd->cmd_name = cmd->full_cmd[0];
	return (CMD_OK);
}

uint32_t	count_redirections(t_list *tokens)
{
	uint32_t	cnt;

	cnt = 0;
	while (tokens)
	{
		if (is_redirection(tokens))
			cnt++;
		tokens = tokens->next;
	}
	return (cnt);
}

t_cmd_status	\
	get_redirections(t_cmd *cmd, t_list *tokens, int order, char *hd)
{
	uint32_t	i;
	char		*here_doc_file;

	cmd->redirections = ft_calloc(cmd->n_redirect, sizeof(t_red_type));
	if (cmd->redirections == NULL)
		return (CMD_MEM_ERR);
	i = 0;
	while (tokens)
	{
		if (is_redirection(tokens))
		{
			cmd->redirections[i] = get_type_redirection(tokens->content);
			tokens = tokens->next;
			if (cmd->redirections[i++] != RED_IN_DOUBLE)
				continue ;
			here_doc_file = create_file_name(HERE_DOC_FIX, hd, order);
			if (here_doc_file == NULL)
				return (ft_free(cmd->redirections), CMD_MEM_ERR);
			ft_free(tokens->content);
			tokens->content = here_doc_file;
		}
		tokens = tokens->next;
	}
	return (CMD_OK);
}

t_cmd_status	get_files(t_cmd *cmd, t_list *tokens)
{
	uint32_t		i;

	cmd->files = ft_calloc(cmd->n_redirect + 1, sizeof(char *));
	if (cmd->files == NULL)
		return (CMD_MEM_ERR);
	i = 0;
	while (tokens)
	{
		if (is_redirection(tokens))
		{
			tokens = tokens->next;
			cmd->files[i] = remove_quotes(tokens->content, false);
			if (cmd->files[i] == NULL)
				return (ft_free(cmd->files), CMD_MEM_ERR);
			i++;
		}
		tokens = tokens->next;
	}
	return (CMD_OK);
}
