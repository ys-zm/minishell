/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:37:50 by faru              #+#    #+#             */
/*   Updated: 2023/05/27 19:38:12 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(const char *str)
{
	size_t	lenght_str;
	char	*new_str;

	lenght_str = ft_strlen(str);
	new_str = ft_calloc(lenght_str + 1, sizeof(char));
	if (! new_str)
		return (NULL);
	else
	{
		while (lenght_str--)
			new_str[lenght_str] = str[lenght_str];
		return (new_str);
	}
}
