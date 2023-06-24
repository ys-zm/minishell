/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/27 17:20:39 by fra           #+#    #+#                 */
/*   Updated: 2023/06/24 23:42:20 by fra           ########   odam.nl         */
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
		if (is_valid_char(string, curr_pos, '|') == true)
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
	if (input_cmd[i] == '\0')
	{
		cmds[i] = ft_strdup("");
		if (cmds[i] == NULL)
			return (ft_free(cmds));
	}
	while (*input_cmd)
	{
		len = 0;
		while (input_cmd[len])
		{
			if (is_valid_char(input_cmd, len, '|'))
				break ;
			len++;
		}
		cmds[i] = ft_substr(input_cmd, 0, len);
		if (cmds[i] == NULL)
			return (ft_free_double((void **) cmds, i));
		i++;
		input_cmd += len + (input_cmd[len] != 0);
	}
	return (cmds);
}

int32_t	isolate_word(char *input, char **new_word)
{
	int32_t		len;

	len = 0;
	while (ft_isspace(input[len]))
		len++;
	while (input[len])
	{
		if (is_valid_space(input, len))
			break ;
		else if (is_valid_arrow(input, len) && *new_word && (! is_valid_arrow(*new_word, 0)))
			break ;
		else if (! is_valid_arrow(input, len) && *new_word && is_valid_arrow(input, len - 1))
			break ;
		else
		{
			*new_word = ft_append_char(*new_word, input[len]);
			if (*new_word == NULL)
				return (-1);
			len++;
		}
	}
	if (*new_word)
	{
		*new_word = ft_trim(*new_word);
		if (*new_word == NULL)
			return (-1);
	}
	return (len);
}

t_list	*tokenize(char *input)
{
	char	*new_word;
	int32_t	len_word;
	t_list	*tokens;
	t_list	*new_token;

	tokens = NULL;
	while (*input)
	{
		new_word = NULL;
		len_word = isolate_word(input, &new_word);
		if (len_word == -1)
			return (ft_lstclear(&tokens, ft_free));
		if (new_word)
		{
			new_token = ft_lstnew(new_word);
			if (new_token == NULL)
			{
				ft_free(new_word);
				return (ft_lstclear(&tokens, ft_free));
			}
			ft_lstadd_back(&tokens, new_token);
		}
		input += len_word;
	}
	return (tokens);
}

