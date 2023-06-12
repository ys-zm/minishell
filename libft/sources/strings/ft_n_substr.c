/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_n_substr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/26 03:30:13 by fra           #+#    #+#                 */
/*   Updated: 2023/02/26 03:30:50 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_n_substr(char const *str, char char_split)
{
	size_t	cnt;
	size_t	reset;

	cnt = 0;
	reset = 1;
	while (str && *str)
	{
		if (*str != char_split && reset)
		{
			cnt++;
			reset = 0;
		}
		else if (*str == char_split)
			reset = 1;
		str++;
	}
	return (cnt);
}
