/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 21:39:02 by fra           #+#    #+#                 */
/*   Updated: 2023/06/24 23:47:21 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	get_cmd(t_list *tokens, t_cmd *cmd)
{
	uint32_t	i;
	uint32_t	n_words;

	n_words = count_words(tokens);
	if (n_words == 0)
	{
		cmd->full_cmd = NULL;
		cmd->cmd_name = NULL;
		return (true);
	}
	cmd->full_cmd = ft_calloc(count_words(tokens) + 1, sizeof(char *));
	if (cmd->full_cmd == NULL)
		return (false);
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
				return (false);
			}
			i++;
		}
		tokens = tokens->next;
	}
	cmd->cmd_name = *(cmd->full_cmd);
	return (true);
}

bool	get_redirections(t_list *tokens, t_cmd *cmd, int32_t order_cmd)
{
	uint32_t	i;
	char		*here_doc_file;

	cmd->n_redirect = count_redirections(tokens);
	if (cmd->n_redirect == 0)
	{
		cmd->redirections = NULL;
		cmd->files = NULL;
		return (true);
	}
	cmd->redirections = ft_calloc(cmd->n_redirect, sizeof(t_red_type));
	if (cmd->redirections == NULL)
		return (false);
	cmd->files = ft_calloc(cmd->n_redirect + 1, sizeof(char *));
	if (cmd->files == NULL)
	{
		ft_free(cmd->redirections);
		return (false);
	}
	i = 0;
	while (tokens)
	{
		if (is_redirection(tokens))
		{
			cmd->redirections[i] = get_type_redirection(tokens->content);
			tokens = tokens->next;
			if (cmd->redirections[i] == RED_IN_DOUBLE)
			{
				here_doc_file = create_file_name(HERE_DOC_FIX, order_cmd);
				if (here_doc_file == NULL)
				{
					ft_free(cmd->redirections);
					ft_free(cmd->files);
					return (false);
				}
				ft_free(tokens->content);
				tokens->content = here_doc_file;
			}
			cmd->files[i] = remove_quotes(tokens->content, false);
			if (cmd->files[i] == NULL)
			{
				ft_free(cmd->redirections);
				ft_free(cmd->files);
				return (false);
			}
			i++;
		}
		tokens = tokens->next;
	}
	return (true);
}

bool	is_redirection(t_list *token)
{	
	char	*word;

	if (token->next == NULL)
		return (false);
	word = token->content;
	if (is_quote(*word))
		word++;
	if (! is_arrow(*word++))
		return (false);
	if (is_quote(*word))
		word++;
	if (*word == '\0')
		return (true);
	else if (is_arrow(*word++))
	{
		if (is_quote(*word))
			word++;
		return (*word == '\0');
	}
	else
		return (false);
}
