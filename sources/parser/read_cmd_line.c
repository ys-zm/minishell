/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_cmd_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 11:03:02 by faru          #+#    #+#                 */
/*   Updated: 2023/06/22 15:07:17 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_status	ft_readline(char **buffer, const char *prompt, bool sintax)
{
	char	*new_string;

	new_string = readline(prompt);
	if (! new_string)
		return (CMD_EOF);
	*buffer = ft_strdup(new_string);
	ft_free(new_string);
	if (*buffer == NULL)
		return (CMD_MEM_ERR);
	else if (sintax && (check_sintax(*buffer) == false))
		return (CMD_SIN_ERR);
	else
		return (CMD_OK);
}

t_cmd_status	aquire_cmd(char **cmd)
{
	t_cmd_status	status;
	char			*buffer;
	uint32_t		cnt;

	buffer = NULL;
	status = ft_readline(&buffer, PROMPT, true);
	if ((status == CMD_EOF) || (status == CMD_MEM_ERR))
		return (status);
	cnt = 0;
	while (status == CMD_OK)
	{
		if (handle_here_doc(buffer, &cnt) == -1)
		{
			ft_free(buffer);
			ft_free(*cmd);
			return (CMD_MEM_ERR);
		}
		*cmd = ft_strjoin(*cmd, buffer, "\n", true);
		if (*cmd == NULL)
			return (CMD_MEM_ERR);
		if (has_trailing_pipe(*cmd) == false)
			break ;
		status = ft_readline(&buffer, "> ", false);
	}
	if (status == CMD_OK)
	{
		*cmd = ft_trim(*cmd);
		if (*cmd == NULL)
			return (CMD_MEM_ERR);
		else if (**cmd == '\0')
			return (CMD_EMPTY);
		else
			return (CMD_OK);
	}
	else
		return (status);
}

t_cmd	*create_new_cmd(char *cmd_str, t_var *depo)
{
	char		**str_cmds;
	char		*exp_var_cmd;
	bool		cmd_status;
	t_cmd		*cmd;
	t_list		*tokens;
	uint32_t	i;

	exp_var_cmd = expand_vars(cmd_str, *(depo->env_list));
	if (exp_var_cmd == NULL)
		return (NULL);
	depo->n_cmd = n_cmds(exp_var_cmd);
	str_cmds = split_into_cmds(exp_var_cmd);
	ft_free(exp_var_cmd);
	if (str_cmds == NULL)
		return (NULL);
	cmd = ft_calloc(depo->n_cmd, sizeof(t_cmd));
	if (cmd == NULL)
		return (ft_free_double((void **) str_cmds, -1));
	i = 0;
	while (i < depo->n_cmd)
	{
		cmd[i].fd_in = 0;
		cmd[i].fd_out = 1;
		tokens = tokenize(str_cmds[i]);
		if (tokens == NULL)
		{
			ft_free_cmd_arr(cmd, i);
			return (ft_free_double((void **) str_cmds, -1));
		}
		cmd_status = get_cmd(tokens, cmd + i);
		if (cmd_status == false)
		{
			ft_lstclear(&tokens, ft_free);
			ft_free_cmd_arr(cmd, i);
			return (ft_free_double((void **) str_cmds, -1));
		}
		cmd_status = get_redirections(tokens, cmd + i, i + 1);
		if (cmd_status == false)
		{
			ft_lstclear(&tokens, ft_free);
			ft_free_cmd_arr(cmd, i);
			ft_free(cmd->full_cmd);
			return (ft_free_double((void **) str_cmds, -1));
		}
		ft_lstclear(&tokens, ft_free);
		i++;
	}
	ft_free_double((void **) str_cmds, -1);
	return (cmd);
}

void	main_loop(t_var *depo)
{
	t_cmd_status	status;
	char			*new_cmd;

	while (true)
	{
		new_cmd = NULL;
		status = aquire_cmd(&new_cmd);
		if (status == CMD_MEM_ERR)
			malloc_protect(depo);
		else if (status == CMD_EOF)
		{
			if (has_trailing_pipe(new_cmd) == true)
				ft_printf("syntax error\n");
			ft_free(new_cmd);
			break ;
		}
		if (status != CMD_EMPTY)
			add_history(new_cmd);
		if (status == CMD_SIN_ERR)
			ft_printf("syntax error\n");
		if ((status == CMD_OK) && (is_only_spaces(new_cmd) == false))
		{
			depo->cmd_data = create_new_cmd(new_cmd, depo);
			if (depo->cmd_data == NULL)
				malloc_protect(depo);
			print_cmd(depo);
			
			ft_exec(depo);
			if (remove_here_docs(depo) == false)
				malloc_protect(depo);
			ft_free_cmd_arr(depo->cmd_data, depo->n_cmd);
			depo->cmd_data = NULL;
		}
		else
			ft_free(new_cmd);
	}
	clear_history();
}
