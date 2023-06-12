/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:35:04 by fra               #+#    #+#             */
/*   Updated: 2023/05/27 19:50:07 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_xitoa(int n, int capital)
{
	size_t	size;
	char	*str_nbr;
	char	*base;

	size = ft_nbrlen(n, 16);
	str_nbr = ft_calloc(size + 1, sizeof(char));
	if (str_nbr)
	{
		if (capital)
			base = "0123456789ABCDEF";
		else
			base = "0123456789abcdef";
		if (n == 0)
			str_nbr[0] = '0';
		size--;
		while (n)
		{
			str_nbr[size--] = base[n % 16];
			n /= 16;
		}
	}
		
	return (str_nbr);
}
