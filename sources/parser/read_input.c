/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 11:03:02 by faru          #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/06/26 14:25:33 by yzaim         ########   odam.nl         */
=======
/*   Updated: 2023/06/26 15:57:18 by faru          ########   odam.nl         */
>>>>>>> new_fra
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_status	ft_readline(char **buffer, const char *prompt, bool sin_check)
{
	char	*new_string;

	new_string = readline(prompt);
	if (! new_string)
		return (CMD_EOF);
	*buffer = ft_strdup(new_string);
	ft_free(new_string);
	if (*buffer == NULL)
		return (CMD_MEM_ERR);
	else if (sin_check && (check_sintax(*buffer) == false))
		return (CMD_SIN_ERR);
	else
		return (CMD_OK);
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

t_cmd_status	aquire_input(char **input)
{
	t_cmd_status	status;
	char			*buffer;
	uint32_t		cnt;

	buffer = NULL;
	status = ft_readline(&buffer, PROMPT, true);
	if (status != CMD_OK)
		return (input_error(input, buffer, status));
	cnt = 0;
	while (status == CMD_OK)
	{
		if (handle_here_doc(buffer, &cnt) != 0)
			return (ft_free(buffer), ft_free(*input), CMD_MEM_ERR);
		*input = ft_strjoin(*input, buffer, "\n", true);
		if (*input == NULL)
			return (CMD_MEM_ERR);
		if (has_trailing_pipe(*input) == false)
			break ;
		status = ft_readline(&buffer, "> ", true);
		if ((status == CMD_MEM_ERR) || (status == CMD_EOF))
			break ;
	}
	return (status);
}

void	exit_shell(char *input)
{
	if (has_trailing_pipe(input) == true)
		ft_printf("syntax error\n");
	else
		ft_printf("exit\n");
	ft_free(input);
}

void	run_cmd(char *input, t_var *mini)
{
	mini->cmd_data = create_new_cmd(input, mini);
	if (mini->cmd_data == NULL)
		malloc_protect(mini);
	ft_exec(mini);
}
