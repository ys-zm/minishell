/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 11:03:02 by faru          #+#    #+#                 */
/*   Updated: 2023/06/26 14:25:33 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_status	ft_readline(char **buffer, const char *prompt, bool sintax_check)
{
	char	*new_string;

	new_string = readline(prompt);
	if (! new_string)
		return (CMD_EOF);
	*buffer = ft_strdup(new_string);
	ft_free(new_string);
	if (*buffer == NULL)
		return (CMD_MEM_ERR);
	else if (sintax_check && (check_sintax(*buffer) == false))
		return (CMD_SIN_ERR);
	else
		return (CMD_OK);
}

t_cmd_status	aquire_input_hd(char *eof, char **here_doc)
{
	char			*new_line;
	t_cmd_status	status;
	
	while (true)
	{
		status = ft_readline(&new_line, "> ", false);
		if (status == CMD_MEM_ERR)
		{
			ft_free(*here_doc);
			return (status);
		}
		else if (status == CMD_EOF)
		{
			ft_free(*here_doc);
			*here_doc = ft_strdup("");
			if (*here_doc == NULL)
				return (CMD_MEM_ERR);
			else
				return (CMD_EOF);
		}
		else if (ft_strncmp(new_line, eof, ft_strlen(eof)) == 0)
		{
			ft_free(new_line);
			*here_doc = ft_append_char(*here_doc, '\n');
			if (*here_doc == NULL)
				return (CMD_MEM_ERR);
			else
				return (CMD_OK);
		}
		*here_doc = ft_strjoin(*here_doc, new_line, "\n", true);
		if (*here_doc == NULL)
			return (CMD_MEM_ERR);
	}
}

t_cmd_status	aquire_input(char **input)
{
	t_cmd_status	status;
	char			*buffer;
	uint32_t		cnt;

	buffer = NULL;
	status = ft_readline(&buffer, PROMPT, true);
	if (status != CMD_OK)
	{
		if (status == CMD_SIN_ERR)
		{
			*input = ft_strjoin(*input, buffer, "\n", true);
			if (*input == NULL)
				return (CMD_MEM_ERR);
		}
		return (status);
	}
	cnt = 0;
	while (status == CMD_OK)
	{
		if (handle_here_doc(buffer, &cnt) != 0)
		{
			ft_free(buffer);
			ft_free(*input);
			return (CMD_MEM_ERR);
		}
		*input = ft_strjoin(*input, buffer, "\n", true);
		if (*input == NULL)
			return (CMD_MEM_ERR);
		if (has_trailing_pipe(*input) == false)
			break ;
		status = ft_readline(&buffer, "> ", true);
		if ((status == CMD_MEM_ERR) || (status == CMD_EOF))		// <-- check if ctrl+D in piping mode is correct
			break ;
	}
	return (status);
}

void	main_loop(t_var *depo)
{
	t_cmd_status	status;
	char			*input;

	while (true)
	{
		input = NULL;
		status = aquire_input(&input);
		if (status == CMD_MEM_ERR)
			malloc_protect(depo);
		else if (status == CMD_EOF)
		{
			if (has_trailing_pipe(input) == true)
				ft_printf("syntax error\n");
			else
				ft_printf("exit\n");
			ft_free(input);
			break ;
		}
		if (is_empty(input) == false)
			add_history(input);
		if (status == CMD_SIN_ERR)
		{
			ft_printf("minishell: syntax error\n");
			ft_free(input);
		}
		else
		{
			depo->cmd_data = create_new_cmd(input, depo);
			if (depo->cmd_data == NULL)
				malloc_protect(depo);
			//print_cmd(depo);	
			ft_exec(depo);
			if (remove_here_docs(depo) == false)
				malloc_protect(depo);
			ft_free_cmd_arr(depo->cmd_data, depo->n_cmd);
			ft_free_exec_alloc(depo);
			depo->cmd_data = NULL;
			depo->n_cmd = 0;
		}
	}
	clear_history();
}
