/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_string.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:54:31 by fra           #+#    #+#                 */
/*   Updated: 2023/07/01 01:48:21 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

bool	is_empty(char	*to_check)
{
	if (to_check == NULL)
		return (true);
	while (ft_isspace(*to_check))
		to_check++;
	return (*to_check == '\0');
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
