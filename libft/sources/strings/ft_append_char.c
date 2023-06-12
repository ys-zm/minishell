/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 05:18:43 by fra               #+#    #+#             */
/*   Updated: 2023/05/27 19:29:48 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_append_char(char *str, char to_add)
{
	uint32_t	i;
	uint32_t	length;
	char		*tmp;

	if (! to_add)
		return (str);
	length = ft_strlen(str);
	tmp = ft_calloc((length + 2), sizeof(char));
	if (tmp)
	{
		i = 0;
		while (str && i < length)
		{
			tmp[i] = str[i];
			i++;
		}
		tmp[i] = to_add;
	}
	ft_free(str);
	return (tmp);
}
