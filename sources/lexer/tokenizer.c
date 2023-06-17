/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/27 17:20:39 by fra           #+#    #+#                 */
/*   Updated: 2023/06/17 01:57:25 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint32_t	n_cmds(char *string)
{
	uint32_t	cnt;
	uint32_t	curr_pos;

	cnt = 1;
	curr_pos = 0;
	while (string[curr_pos])
	{
		if ((string[curr_pos] == '|') && is_outside_quotes(string, curr_pos))
			cnt++;
		curr_pos++;
	}
	return (cnt);
}

char	**split_into_cmds(char *input_cmd)
{
	char		**cmds;
	uint32_t	i;
	uint32_t	len;

	cmds = ft_calloc(n_cmds(input_cmd) + 1, sizeof(char *));
	if (! cmds)
		return (NULL);
	i = 0;
	while (*input_cmd)
	{
		len = 0;
		while (input_cmd[len])
		{
			if (is_valid_char(input_cmd, len, '|'))
				break ;
			len++;
		}
		cmds[i] = ft_trim(ft_substr(input_cmd, 0, len));
		if (cmds[i] == NULL)
			return (ft_free_double((void **) cmds, i));\
		i++;
		input_cmd += len + (input_cmd[len] != 0);
	}
	return (cmds);
}

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
		if (is_redirection(tokens->content))
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
		if (is_redirection(tokens->content))
			tokens = tokens->next;
		else
		{	
			if ((! ft_strchr(tokens->content, '\'')) || (! ft_strchr(tokens->content, '\"')))
				cmd->full_cmd[i] = remove_quotes(tokens->content);
			else
				cmd->files[i] = ft_strdup(tokens->content);
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
	else
	{
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
			if (is_redirection(tokens->content))	// NB need to check if redirection is inside quotes
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
				if (((! ft_strchr(tokens->content, '\'')) || (! ft_strchr(tokens->content, '\"'))))
					cmd->files[i] = remove_quotes(tokens->content);
				else
					cmd->files[i] = ft_strdup(tokens->content);
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
}

bool	is_redirection(char	*word)
{
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

bool	split_input(t_cmd *cmd, t_list *tokens, int32_t order_cmd)
{
	bool		status;
	// NB must remove quotes before inspection! (or not?)
	status = get_cmd(tokens, cmd);
	if (status == false)
		return (false);
	status = get_redirections(tokens, cmd, order_cmd);
	if (status == false)
	{
		ft_free(cmd->full_cmd);
		return (false);
	}
	return (true);
}

t_red_type	get_type_redirection(char *to_check)
{
	if (is_quote(*to_check))
		to_check++;
	if (*to_check++ == '<')
	{
		if (is_quote(*to_check))
			to_check++;
		if (*to_check == '<')
			return (RED_IN_DOUBLE);
		else
			return (RED_IN_SINGLE);
	}
	else
	{
		if (is_quote(*to_check))
			to_check++;
		if (*to_check == '>')
			return (RED_OUT_DOUBLE);
		else
			return (RED_OUT_SINGLE);
	}
}

t_list	*tokenize(char *input)
{
	char			*new_word;
	bool        	end_word;
	uint32_t    	len;
	t_list			*tokens;
	t_list			*new_token;

	tokens = NULL;
	while (*input)
	{
		len = 0;
		end_word = false;
		new_word = NULL;
		while (! end_word)
		{
			if (input[len] == '\0')
				end_word = true;
			else if (is_valid_space(input, len))
			{
				while (ft_isspace(input[len]))
					len++;
				end_word = true;
			}
			else if (is_valid_arrow(input, len) && new_word && (! is_valid_arrow(new_word, 0)))
				end_word = true;
			else if (! is_valid_arrow(input, len) && new_word && is_valid_arrow(input, len - 1))
				end_word = true;
			else
			{
				new_word = ft_append_char(new_word, input[len]);
				if (new_word == NULL)
				{
					ft_lstclear(&tokens, ft_free);
					return (NULL);
				}
				len++;
				if (input[len] == '\0')
					end_word = true;
			}
		}
		if (new_word)
		{
			new_word = ft_trim(new_word);
			if (new_word == NULL)
			{
				ft_lstclear(&tokens, ft_free);
				return (NULL);
			}
			new_token = ft_lstnew(new_word);
			if (new_token == NULL)
			{
				ft_lstclear(&tokens, ft_free);
				return (NULL);
			}
			ft_lstadd_back(&tokens, new_token);
		}
		input += len;
	}
	return (tokens);
}

