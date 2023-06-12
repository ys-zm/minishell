/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_part_int.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 07:01:39 by fra           #+#    #+#                 */
/*   Updated: 2023/03/19 03:49:36 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_part_int(float number)
{
	if (number < 0)
		return ((int) number / 1 - 1);
	else
		return ((int) number / 1);
}
