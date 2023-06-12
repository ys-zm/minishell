/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 19:44:45 by faru          #+#    #+#                 */
/*   Updated: 2023/02/23 22:26:22 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *str, char *to_find, size_t len)
{
	size_t	len_to_find;
	size_t	all_chars;

	len_to_find = ft_strlen(to_find);
	if (ft_strlen(to_find) == 0 || ! str)
		return ((char *) str);
	while (*str && len)
	{
		all_chars = 0;
		while (*str && *to_find && len && *str == *to_find)
		{
			all_chars++;
			str++;
			to_find++;
			len--;
		}
		if (all_chars == len_to_find)
			return ((char *)(str - all_chars));
		to_find -= all_chars;
		str -= all_chars - 1;
		len += all_chars - 1;
	}
	return (NULL);
}
