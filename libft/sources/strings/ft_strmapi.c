/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:28:31 by anonymous         #+#    #+#             */
/*   Updated: 2023/05/27 19:31:56 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	size_t	length;
	char	*new_str;

	if (! str || ! f)
		return (NULL);
	length = ft_strlen(str);
	new_str = ft_calloc(length + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (length--)
		new_str[length] = f(length, str[length]);
	return (new_str);
}
