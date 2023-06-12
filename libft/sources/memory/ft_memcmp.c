/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 11:47:01 by faru          #+#    #+#                 */
/*   Updated: 2023/03/06 04:46:11 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *src, const void *dst, size_t n)
{
	const char		*c_src;
	const char		*c_dst;
	size_t			cnt;

	c_src = (const char *) src;
	c_dst = (const char *) dst;
	cnt = 0;
	if (! n)
		return (0);
	while (cnt < n && c_src[cnt] && c_dst[cnt])
	{
		if (c_src[cnt] != c_dst[cnt])
			return ((unsigned char) c_src[cnt] - (unsigned char) c_dst[cnt]);
		cnt++;
	}
	if (cnt == n || (! c_src[cnt] && ! c_dst[cnt]))
		return (0);
	else
		return (-1);
}
