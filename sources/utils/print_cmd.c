/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 19:22:21 by faru          #+#    #+#                 */
/*   Updated: 2023/07/01 19:33:15 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	print_cmd(t_var	*mini)
{
	uint32_t	i;
	uint32_t	j;

	j = 0;
	if (mini == NULL)
		return;
	while (j < mini->n_cmd)
	{
		ft_printf("COMMAND\n\tcmd name: %s\n", mini->cmd_data[j].cmd_name);
		i = 0;
		while (mini->cmd_data[j].full_cmd && mini->cmd_data[j].full_cmd[i])
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