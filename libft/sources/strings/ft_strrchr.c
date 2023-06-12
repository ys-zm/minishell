/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 11:17:44 by faru          #+#    #+#                 */
/*   Updated: 2022/10/17 19:44:11 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *str_to_search, int to_find)
{
	size_t			pos;
	unsigned char	uc_to_find;

	uc_to_find = (unsigned char) to_find;
	if (! str_to_search)
		return (NULL);
	pos = ft_strlen(str_to_search);
	if (uc_to_find == 0)
		return ((char *)(str_to_search + pos));
	while (pos--)
	{
		if (str_to_search[pos] == uc_to_find)
			return ((char *)(str_to_search + pos));
	}
	return (NULL);
}
