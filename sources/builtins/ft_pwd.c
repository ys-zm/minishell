/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 13:22:13 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/12 16:57:16 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

void	ft_print_pwd(char *curr_dir, int fd_out)
{
	ft_putstr_fd(curr_dir, fd_out);
	ft_putstr_fd("\n", fd_out);
}
//ft_pwd: print working directory
int	ft_pwd(t_var *mini, char **args, int fd_out)
{
	char	*curr_dir;

	(void)mini;
	if (args[1])
		return (ft_putstr_fd("pwd: bad option: try pwd with no option\n", 2), \
			EXIT_FAILURE);
	curr_dir = getcwd(0, 0);
	if (curr_dir)
	{
		ft_print_pwd(curr_dir, fd_out);
		return (free(curr_dir), EXIT_SUCCESS);
	}
	curr_dir = ft_find_env_val(mini->env_list, "PWD");
	if (curr_dir)
		return (ft_print_pwd(curr_dir, fd_out), EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
