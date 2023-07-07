/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:26 by fra           #+#    #+#                 */
/*   Updated: 2023/07/07 11:44:50 by faru          ########   odam.nl         */
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
	uint32_t	len;

	cmds = ft_calloc(n_cmds(input) + 1, sizeof(char *));
	if (! cmds)
		return (NULL);
	i = 0;
	while (true)
	{
		len = 0;
		while (input[len] && (is_valid_symbol(input, len, '|') == false))
			len++;
		cmds[i] = ft_substr(input, 0, len);
		if (cmds[i] == NULL)
			return (ft_free_double((void **) cmds, i));
		i++;
		input += len + (input[len] != 0);
		if (*input == '\0')
			break ;
	}
	return (cmds);
}

t_cmd	*create_new_cmd(char *cmd_input, t_var *mini)
{
	char		**str_cmds;
	t_cmd		*cmd;
	uint32_t	i;

	cmd_input = expander(cmd_input, *(mini->env_list));
	if (cmd_input == NULL)
		return (NULL);
	mini->n_cmd = n_cmds(cmd_input);
	str_cmds = split_into_cmds(cmd_input);
	ft_free(cmd_input);
	if (str_cmds == NULL)
		return (NULL);
	cmd = ft_calloc(mini->n_cmd, sizeof(t_cmd));
	if (cmd == NULL)
		return (ft_free_double((void **) str_cmds, -1));
	i = 0;
	while (i < mini->n_cmd)
	{
		if (build_cmd(cmd + i, str_cmds[i], i + 1) == NULL)
			return (ft_free_cmd_arr(cmd, i + 1), \
				ft_free_double((void **) str_cmds, -1));
		i++;
	}
	ft_free_double((void **) str_cmds, -1);
	return (cmd);
}
