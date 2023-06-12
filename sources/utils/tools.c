/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/20 19:09:49 by fra           #+#    #+#                 */
/*   Updated: 2023/06/11 18:41:15 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint32_t	skip_redirect_chars(char *cmd, uint32_t pos)
{
	uint32_t	start_pos;

	start_pos = pos;
	while (is_valid_arrow(cmd, pos))
	{
		pos++;
		pos += is_arrow(cmd[pos]);
		while (ft_isspace(cmd[pos]))
			pos++;
		while (! is_valid_space(cmd, pos) && (! is_valid_arrow(cmd, pos)) && cmd[pos])
			pos++;
	}
	return (pos - start_pos);
}

bool	is_only_spaces(char	*to_check)
{
	while (ft_isspace(*to_check))
		to_check++;
	return (*to_check == '\0');
}

char	*remove_quotes(char *to_clear)
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
	cleaned_str = ft_calloc(len + 1, sizeof(char));
	if (! cleaned_str)
		return (NULL);
	i = 0;
	j = 0;
	while (to_clear[j])
	{
		if (! is_valid_quote(to_clear, j))
			cleaned_str[i++] = to_clear[j];
		j++;
	}
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

void	print_cmd(t_var	*mini)
{
	uint32_t	i;
	uint32_t	j;
	
	j = 0;
	while (j < mini->n_cmd)
	{
		ft_printf("COMMAND\n\tcmd name: %s\n", mini->cmd_data[j].cmd_name);
		i = 0;
		while (mini->cmd_data[j].full_cmd[i])
			ft_printf("\t\targ: %s\n", mini->cmd_data[j].full_cmd[i++]);
		if (mini->cmd_data[j].redirections)
		{
			// ft_printf("\tn. redirections: %u\n", mini->cmd_data[j].n_redirect);
			i = 0;
			while (i < mini->cmd_data[j].n_redirect)
			{
				if (mini->cmd_data[j].redirections[i] == RED_IN_SINGLE)
					ft_printf("\t\tred type: %s file: %s\n", "<", mini->cmd_data[j].files[i]);
				else if (mini->cmd_data[j].redirections[i] == RED_OUT_SINGLE)
					ft_printf("\t\tred type: %s file: %s\n", ">", mini->cmd_data[j].files[i]);
				else if (mini->cmd_data[j].redirections[i] == RED_IN_DOUBLE)
					ft_printf("\t\tred type: %s file: %s\n", "<<", mini->cmd_data[j].files[i]);
				else if (mini->cmd_data[j].redirections[i] == RED_OUT_DOUBLE)
					ft_printf("\t\tred type: %s file: %s\n", ">>", mini->cmd_data[j].files[i]);
				i++;
			}
		}
		j++;
	}
}

uint32_t	get_order_cmd(char *str, uint32_t pos)
{
	uint32_t	i;
	uint32_t	order;
	char		*next_pipe;
	uint32_t	pipe_pos;

	i = 0;
	order = 1;
	pipe_pos = 0;
	while (true)
	{
		while (true)
		{
			next_pipe = ft_strchr(str + pipe_pos, '|');
			if (next_pipe == NULL)
				return (order);
			pipe_pos = next_pipe - str;
			if (is_valid_char(str, pipe_pos, '|'))
				break ;
		}
		if (pos > pipe_pos)
		{
			order++;
			pipe_pos++;
		}
		else
			break ;
	}
	return (order); 
}
