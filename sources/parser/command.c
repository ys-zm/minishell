/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:26 by fra           #+#    #+#                 */
/*   Updated: 2023/09/16 23:03:01 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

uint32_t	n_cmds(char *string)
{
	uint32_t	cnt;
	uint32_t	curr_pos;

	cnt = 1;
	curr_pos = 0;
	while (string[curr_pos])
	{
		if (is_valid_symbol(string, curr_pos, '|') == true)
			cnt++;
		curr_pos++;
	}
	return (cnt);
}

char	**split_into_cmds(char *input)
{
	char		**cmds;
	uint32_t	i;
	uint32_t	j;
	uint32_t	len;

	cmds = ft_calloc(n_cmds(input) + 1, sizeof(char *));
	if (! cmds)
		return (NULL);
	i = 0;
	j = 0;
	while (true)
	{
		len = 0;
		while (input[j + len] && is_valid_symbol(input, j + len, '|') == false)
			len++;
		cmds[i] = ft_substr(input + j, 0, len);
		if (cmds[i] == NULL)
			return (ft_free_double((void **) cmds, i));
		i++;
		j += len + (input[j + len] != 0);
		if (input[j] == '\0')
			break ;
	}
	ft_free(input);
	return (cmds);
}

t_cmd_status	create_new_cmd(char *cmd_input, t_var *mini)
{
	char			**cmds;
	t_cmd_status	status;
	uint32_t		i;

	status = expander(&cmd_input, mini->env_list, mini->status, true);
	if (status != CMD_OK)
		return (status);
	mini->n_cmd = n_cmds(cmd_input);
	cmds = split_into_cmds(cmd_input);
	if (cmds == NULL)
		return (CMD_MEM_ERR);
	mini->cmd_data = ft_calloc(mini->n_cmd, sizeof(t_cmd));
	if (mini->cmd_data == NULL)
		return (ft_free_double((void **) cmds, -1), CMD_MEM_ERR);
	i = 0;
	while (i < mini->n_cmd)
	{
		status = build_cmd(mini->cmd_data + i, cmds[i], i + 1, mini->hd_path);
		if (status != CMD_OK)
			break ;
		i++;
	}
	if (status != CMD_OK)
		ft_free_cmd_arr(mini);
	return (ft_free_double((void **) cmds, -1), status);
}
