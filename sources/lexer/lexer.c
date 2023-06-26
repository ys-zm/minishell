/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 21:39:02 by fra           #+#    #+#                 */
/*   Updated: 2023/06/26 12:40:42 by faru          ########   odam.nl         */
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

char	**fill_words(t_list *tokens)
{
	char		**full_cmd;
	uint32_t	i;

	full_cmd = ft_calloc(count_words(tokens) + 1, sizeof(char *));
	if (full_cmd == NULL)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (is_redirection(tokens))
			tokens = tokens->next;
		else
		{
			full_cmd[i] = remove_quotes(tokens->content, false);
			if (full_cmd[i] == NULL)
				return (ft_free(full_cmd));
			i++;
		}
		tokens = tokens->next;
	}
	return (full_cmd);
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

t_red_type	*get_redirections(t_list *tokens, uint32_t n_redirect, int order)
{
	uint32_t	i;
	char		*here_doc_file;
	t_red_type	*redirections;

	redirections = ft_calloc(n_redirect, sizeof(t_red_type));
	if (redirections == NULL)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (is_redirection(tokens))
		{
			redirections[i] = get_type_redirection(tokens->content);
			tokens = tokens->next;
			if (redirections[i++] != RED_IN_DOUBLE)
				continue ;
			here_doc_file = create_file_name(HERE_DOC_FIX, order);
			if (here_doc_file == NULL)
				return (ft_free(redirections));
			ft_free(tokens->content);
			tokens->content = here_doc_file;
		}
		tokens = tokens->next;
	}
	return (redirections);
}

char	**get_files(t_list *tokens, uint32_t n_redirect)
{
	uint32_t	i;
	char		**files;

	files = ft_calloc(n_redirect + 1, sizeof(char *));
	if (files == NULL)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (is_redirection(tokens))
		{
			tokens = tokens->next;
			files[i] = remove_quotes(tokens->content, false);
			if (files[i] == NULL)
				return (ft_free(files));
			i++;
		}
		tokens = tokens->next;
	}
	return (files);
}
