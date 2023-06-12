/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 23:58:24 by anonymous     #+#    #+#                 */
/*   Updated: 2023/03/06 04:53:13 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_striteri(char *str, void (*f)(unsigned int, char*))
{
	size_t	length;

	if (str && f)
	{
		length = ft_strlen(str);
		str[length] = '\0';
		while (length--)
			f(length, str + length);
	}
}
