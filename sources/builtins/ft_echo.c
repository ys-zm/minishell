/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 14:25:47 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/01 01:48:21 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

t_env	*ft_find_node(t_env *env_list, char *key)
{
	while (env_list->next != NULL)
	{
		if (!ft_strcmp(env_list->key, key))
			break ;
		env_list = env_list->next;
	}
	if (!ft_strcmp(env_list->key, key))
		return (env_list);
	else
		return (NULL);
}

void	ft_print_echo(char **args, int i, int fd_out)
{
	while (args && args[i])
	{
		ft_putstr_fd(args[i], fd_out);
		if (args[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
}

//edge case: echo $?weoiruyfh ours outputs nothing
//$? outputs
// minishell: 0: command not found i our one
//echo - does not work
int	ft_echo(char **args, int fd_out)
{
	bool	new_line;
	int		i;
	int		j;

	i = 1;
	new_line = 1;
	if (count_args(args) == 1)
		return (ft_putstr_fd("\n", fd_out), EXIT_SUCCESS);
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
			new_line = 0;
		else
			break ;
		i++;
	}
	ft_print_echo(args, i, fd_out);
	if (new_line)
		ft_putstr_fd("\n", fd_out);
	return (EXIT_SUCCESS);
}
