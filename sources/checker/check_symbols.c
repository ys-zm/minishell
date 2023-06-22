/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_symbols.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 00:55:08 by fra           #+#    #+#                 */
/*   Updated: 2023/06/22 12:02:15 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool	is_valid_char(char *string, uint32_t pos_to_check, char symbol)
{
	if (string[pos_to_check] != symbol)
		return (false);
	else
		return (is_outside_quotes(string, pos_to_check));
}

bool	is_valid_space(char *string, uint32_t pos_to_check)
{
	if (! ft_isspace(string[pos_to_check]))
		return (false);
	else
		return (is_outside_quotes(string, pos_to_check));
}

bool	is_valid_arrow(char *string, uint32_t pos_to_check)
{
	if (! is_arrow(string[pos_to_check]))
		return (false);
	else
		return (is_outside_quotes(string, pos_to_check));
}

bool	is_valid_dollar(char *string, uint32_t pos_to_check)
{
	uint32_t	i;
	bool		open_quotes;
	
	if (string[pos_to_check] != '$')
		return (false);
	if ((string[pos_to_check + 1] == '\0' ) || ft_isspace(string[pos_to_check + 1]))
		return (false);
	i = 0;
	open_quotes = false;
	while (i < pos_to_check)
	{
		if (string[i] == '\'')
			open_quotes = ! open_quotes;
		i++;
	}
	return (! open_quotes);
}

bool	is_valid_quote(char *string, uint32_t pos_to_check)
{
	uint32_t	i;
	char		open_quote;

	if (! is_quote(string[pos_to_check]))
		return (false);
	else if (is_outside_quotes(string, pos_to_check))
		return (true);
	else
	{
		i = 0;
		open_quote = '\0';
		while (i < pos_to_check)
		{
			if (is_quote(string[i]))
			{
				if (string[i] == open_quote)
					open_quote = '\0';
				else if (open_quote == '\0')
					open_quote = string[i];
			}
			i++;
		}
		return (string[pos_to_check] == open_quote);
	}
}
