/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/27 17:20:39 by fra           #+#    #+#                 */
/*   Updated: 2023/06/28 10:01:43 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if (is_valid_arrow(input, len) && *new_word && \
			(! is_valid_arrow(*new_word, 0)))
			break ;
		else if (! is_valid_arrow(input, len) && *new_word && \
			is_valid_arrow(input, len - 1))
			break ;
		else
		{
			*new_word = ft_append_char(*new_word, input[len++]);
			if (*new_word == NULL)
				return (-1);
		}
	}
	return (len);
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
