/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_index.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 03:00:27 by fra           #+#    #+#                 */
/*   Updated: 2023/03/20 01:39:06 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_index(char *str, char value)
{
	int	cnt;

	cnt = -1;
	while (str && *str != value)
	{
		cnt++;
		str++;
	}
	return (cnt);
}
