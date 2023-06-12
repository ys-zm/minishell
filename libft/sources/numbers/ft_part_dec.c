/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_part_dec.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 07:08:25 by fra           #+#    #+#                 */
/*   Updated: 2023/03/19 03:50:02 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_part_dec(float number)
{
	if (number > 0)
		return (number - ft_part_int(number));
	else
		return (number - ft_part_int(number) - 1);
}
