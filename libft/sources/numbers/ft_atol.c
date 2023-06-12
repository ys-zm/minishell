/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 16:12:33 by faru          #+#    #+#                 */
/*   Updated: 2023/02/11 00:17:24 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

long	ft_atol(const char *str)
{
	int		sign;
	size_t	nbr;

	nbr = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
		nbr = (nbr * 10) + (*str++ - '0');
	return (((long) nbr) * sign);
}
