/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_long.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 23:55:44 by fra           #+#    #+#                 */
/*   Updated: 2023/03/04 22:39:56 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_long(char *number)
{
	if (ft_is_number(number))
	{
		if (! ft_strchr(number, '.') && ! ft_strchr(number, ','))
			return (1);
	}
	return (0);
}
