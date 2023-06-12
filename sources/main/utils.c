/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 17:27:23 by yzaim         #+#    #+#                 */
/*   Updated: 2023/06/12 15:08:50 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    set_up_struct(t_var **mini, char **envp)
{
	*mini = ft_calloc(1, sizeof(t_var));
	if (*mini == NULL)
		return (EXIT_FAILURE);
	(*mini)->cmd_data = NULL;
	(*mini)->n_cmd = 0;
	(*mini)->env_list = NULL;
	make_env_list(envp, *mini);
	(*mini)->env_arr = NULL;
	(*mini)->paths = NULL;
	(*mini)->pipes = NULL;
	(*mini)->pid = NULL;
	return (EXIT_SUCCESS);
}
