/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 16:42:53 by faru          #+#    #+#                 */
/*   Updated: 2023/03/20 02:44:51 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t max_chars)
{
	size_t	index;

	index = 0;
	if (max_chars)
	{
		while (index < max_chars - 1 && src[index] != '\0')
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (max_chars);
}
