/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:09:17 by anonymous         #+#    #+#             */
/*   Updated: 2023/05/27 19:49:15 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_itoa(int n)
{
	char	*str_nbr;
	long	l_n;
	size_t	n_digits;

	l_n = (long) n;
	if (n < 0)
		l_n *= -1;
	n_digits = ft_nbrlen(l_n, 10) + (n < 0);
	str_nbr = ft_calloc(n_digits + 1, sizeof(char));
	if (str_nbr)
	{
		n_digits--;
		while (l_n)
		{
			str_nbr[n_digits--] = l_n % 10 + '0';
			l_n /= 10;
		}
		if (n < 0)
			str_nbr[n_digits] = '-';
		else if (n == 0)
			str_nbr[n_digits] = '0';
	}
	return (str_nbr);
}
