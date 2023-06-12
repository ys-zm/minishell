/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_occ.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/11 23:23:57 by fra           #+#    #+#                 */
/*   Updated: 2023/02/26 03:29:34 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_occ(char *str, char to_find)
{
	int	count;

	count = 0;
	str = ft_strchr(str, to_find);
	while (str++)
	{
		count++;
		str = ft_strchr(str, to_find);
	}
	return (count);
}
