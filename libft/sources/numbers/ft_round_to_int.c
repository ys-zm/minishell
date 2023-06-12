/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_round_to_int.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/12 05:17:11 by fra           #+#    #+#                 */
/*   Updated: 2023/03/12 06:06:24 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_round_to_int(double number)
{
	int		sign;
	long	tmp;
	int		last_digit;

	sign = 0;
	if (number < 0)
	{
		number *= -1;
		sign++;
	}
	if (!(number - ft_part_int(number)))
	{
		if (sign)
			number *= -1;
		return ((int) number);
	}
	tmp = ft_part_int(number * 10);
	last_digit = tmp - ((tmp / 10) * 10);
	if (last_digit > 4 && ! sign)
		number += 1;
	else if (last_digit < 5 && sign)
		number -= 1;
	if (sign)
		number *= -1;
	return (ft_part_int(number));
}
