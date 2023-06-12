/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_int.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 23:54:33 by fra           #+#    #+#                 */
/*   Updated: 2023/03/04 22:41:54 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_int(char *number)
{
	if (ft_is_long(number))
	{
		if (! (ft_atoi(number) - ft_atol(number)))
			return (1);
	}
	return (0);
}
