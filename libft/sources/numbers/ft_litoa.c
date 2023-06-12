/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:33:53 by fra               #+#    #+#             */
/*   Updated: 2023/05/27 19:48:24 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_litoa(long n)
{
	char	*str_nbr;
	size_t	tmp;
	size_t	n_digits;

	if (n < 0)
		tmp = n * -1;
	else
		tmp = n;
	n_digits = ft_nbrlen(tmp, 10) + (n < 0);
	str_nbr = ft_calloc(n_digits + 1, sizeof(char));
	if (str_nbr)
	{
		n_digits--;
		while (tmp)
		{
			str_nbr[n_digits--] = tmp % 10 + '0';
			tmp /= 10;
		}
		if (n < 0)
			str_nbr[n_digits] = '-';
		else if (n == 0)
			str_nbr[n_digits] = '0';
	}
	return (str_nbr);
}
