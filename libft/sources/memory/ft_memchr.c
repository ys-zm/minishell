/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 11:34:01 by faru          #+#    #+#                 */
/*   Updated: 2023/03/06 04:16:13 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *str_to_search, int to_find, size_t n)
{
	size_t				cnt;
	const unsigned char	*char_str;
	unsigned char		c_to_find;

	cnt = 0;
	char_str = (const unsigned char *) str_to_search;
	c_to_find = (unsigned char) to_find;
	while (cnt < n)
	{
		if (char_str[cnt] == c_to_find)
			return ((void *)(char_str + cnt));
		cnt++;
	}
	return (NULL);
}
