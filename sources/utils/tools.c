/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/20 19:09:49 by fra           #+#    #+#                 */
/*   Updated: 2023/06/24 21:07:40 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_empty(char	*to_check)
{
	if (to_check == NULL)
		return (true);
	while (ft_isspace(*to_check))
		to_check++;
	return (*to_check == '\0');
}

char	*remove_quotes(char *to_clear, bool free_string)
{
	char		*cleaned_str;
	uint32_t	len;
	uint32_t	i;
	uint32_t	j;

	len = ft_strlen(to_clear);
	i = 0;
	while (to_clear[i])
	{
		if (is_valid_quote(to_clear, i))
			len--;
		i++;
	}
	if (i == len)
		cleaned_str = ft_strdup(to_clear);
	else
	{
		cleaned_str = ft_calloc(len + 1, sizeof(char));
		if (cleaned_str)
		{
			i = 0;
			j = 0;
			while (to_clear[j])
			{
				if (! is_valid_quote(to_clear, j))
					cleaned_str[i++] = to_clear[j];
				j++;
			}
		}
	}
	if (free_string == true)
		ft_free(to_clear);
	return (cleaned_str);
}

bool	has_trailing_pipe(char	*cmd)
{
	uint32_t	len_cmd;

	if (! cmd || (*cmd == '\0'))
		return (false);
	len_cmd = ft_strlen(cmd) - 1;
	while (len_cmd && ft_isspace(cmd[len_cmd]))
		len_cmd--;
	if (len_cmd <= 1)
		return (false);
	else
		return (cmd[len_cmd] == '|');
}

bool	is_outside_quotes(char *string, uint32_t pos_to_check)
{
	uint32_t	i;
	char		quotes;
	bool		open_quotes;

	i = 0;
	open_quotes = false;
	while (string[i] && (i < pos_to_check))
	{
		if (is_quote(string[i]))
		{
			if ((open_quotes == true) && (string[i] == quotes))
			{
				quotes = '\0';
				open_quotes = false;
			}
			else if (open_quotes == false)
			{
				quotes = string[i];
				open_quotes = true;
			}
		}
		i++;
	}
	return (! open_quotes);
}

bool	is_quote(char to_check)
{
	return ((to_check == '\'') || (to_check == '\"'));
}

bool	is_arrow(char to_check)
{
	return ((to_check == '<') || (to_check == '>'));
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
