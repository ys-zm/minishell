/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 11:03:02 by faru          #+#    #+#                 */
/*   Updated: 2023/07/08 20:01:00 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

t_cmd_status	ft_readline(char **buffer, const char *prompt, bool sin_check)
{
	char	*new_string;

	new_string = readline(prompt);
	if (! new_string)
		return (CMD_CTRL_D);
	*buffer = ft_strdup(new_string);
	ft_free(new_string);
	if (*buffer == NULL)
		return (CMD_MEM_ERR);
	else if (sin_check && (check_sintax(*buffer) == false))
		return (CMD_SIN_ERR);
	else
		return (CMD_OK);
}

bool	update_status(t_cmd_status to_check)
{
	if (to_check == CMD_CTRL_D)
		to_check = CMD_SIN_ERR;
	return (to_check);
}

t_cmd_status	input_error(char **input, char *buffer, t_cmd_status status)
{
	if (status == CMD_SIN_ERR)
	{
		*input = ft_strjoin(*input, buffer, "\n", true);
		if (*input == NULL)
			return (CMD_MEM_ERR);
	}
	return (status);
}

t_cmd_status	aquire_input(char **input, t_var *mini)
{
	t_cmd_status	status;
	char			*buffer;
	uint32_t		cnt;

	buffer = NULL;
	rl_outstream = stderr;
	status = ft_readline(&buffer, PROMPT, true);
	if (status != CMD_OK)
		return (input_error(input, buffer, status));
	cnt = 0;
	while (status == CMD_OK)
	{
		status = handle_here_doc(buffer, &cnt, mini);
		if ((status != CMD_OK) && (status != CMD_CTRL_C))
			return (ft_free(buffer), ft_free(*input), status);
		*input = ft_strjoin(*input, buffer, "\n", true);
		if (*input == NULL)
			return (CMD_MEM_ERR);
		if (has_trailing_pipe(*input) == false)
			break ;
		status = ft_readline(&buffer, "> ", true);
		if (status != CMD_OK)
			return (update_status(status));
	}
	return (status);
}
