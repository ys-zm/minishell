/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 14:34:51 by yzaim         #+#    #+#                 */
/*   Updated: 2023/07/01 01:48:21 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

int	ft_num_of_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	ft_ifnum(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	ft_if_sign(char *str)
{
	bool	sign;
	int		num;
	int		ret;
	int		sub;

	sign = 0;
	sub = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	num = ft_atoi(str);
	if (sign)
	{
		sub = num / 256;
		ret = 256 - (num - (sub * 256));
	}
	else
		ret = num;
	return (ret);
}

//ft_exit // only hapens in curr process if using pipes!
//sometimes its an exit code1 or 255 when int too long, or non numeric
//if SHLVL exists, decrement shlvl
int	ft_exit(t_var *mini, char **args)
{
	if (mini->n_cmd == 1)
		ft_putstr_fd("exit\n", 1);
	if (count_args(args) == 1)
	{
		ft_free_all(mini);
		exit(g_exit_code);
	}
	if (ft_ifnum(args[1]) == 0)
	{
		ft_write_error(2, "exit", args[1], "numeric argument required");
		g_exit_code = 255;
		exit(g_exit_code);
	}
	else
	{
		if (ft_num_of_args(args) == 2)
		{
			g_exit_code = ft_if_sign(args[1]);
			exit(g_exit_code);
		}
		else
			return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), \
			EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
