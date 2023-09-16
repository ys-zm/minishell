/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_sintax.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 21:26:00 by fra           #+#    #+#                 */
/*   Updated: 2023/09/16 23:23:56 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

bool	check_quotes(char *cmd)
{
	bool	s_quotes_closed;
	bool	d_quotes_closed;

	s_quotes_closed = true;
	d_quotes_closed = true;
	while (*cmd)
	{
		if (*cmd == '\'')
			s_quotes_closed = ! (d_quotes_closed && s_quotes_closed);
		else if (*cmd == '\"')
			d_quotes_closed = ! (s_quotes_closed && d_quotes_closed);
		cmd++;
	}
	return (s_quotes_closed && d_quotes_closed);
}

bool	check_pipes(char *cmd)
{
	uint32_t	i;
	int32_t		last_pipe_pos;

	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '|')
		return (false);
	last_pipe_pos = -1;
	while (cmd[i])
	{
		if ((cmd[i] == '|') && is_outside_quotes(cmd, i))
		{
			if (last_pipe_pos != -1)
			{
				while (ft_isspace(cmd[++last_pipe_pos]))
					;
				if (last_pipe_pos == (int32_t) i)
					return (false);
			}
			last_pipe_pos = i;
		}
		i++;
	}
	return (true);
}

bool	check_redirections(char *cmd)
{
	uint32_t	i;
	char		open_arrow;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (is_valid_arrow(cmd, i))
		{
			open_arrow = cmd[i++];
			if (cmd[i] == open_arrow)
				i++;
			else if (is_arrow(cmd[i]) && (cmd[i] != open_arrow))
				return (false);
			while (ft_isspace(cmd[i]))
				i++;
			if (((cmd[i] == '|') || (is_arrow(cmd[i])) || (cmd[i] == '\0')))
				return (false);
		}
		else
			i++;
	}
	return (true);
}

bool	check_sintax(char *cmd)
{
	bool	quotes;
	bool	pipes;
	bool	redirections;

	quotes = check_quotes(cmd);
	pipes = check_pipes(cmd);
	redirections = check_redirections(cmd);
	if (quotes && pipes && redirections)
		return (true);
	else
	{
		*g_exit_code = 258;
		return (false);
	}
}
