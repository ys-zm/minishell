/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 16:45:43 by faru          #+#    #+#                 */
/*   Updated: 2023/03/20 02:42:27 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	index;
	size_t	max_chars;

	if (dest)
		len_dest = ft_strlen(dest);
	else
		len_dest = 0;
	if (size > len_dest)
	{
		index = 0;
		max_chars = size - len_dest - 1;
		while (index < max_chars && src[index] != '\0')
		{
			dest[len_dest + index] = src[index];
			index++;
		}
		dest[len_dest + index] = '\0';
		return (index);
	}
	else
		return (0);
}
