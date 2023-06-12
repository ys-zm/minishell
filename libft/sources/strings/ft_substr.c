/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:00:52 by faru              #+#    #+#             */
/*   Updated: 2023/05/27 19:31:36 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	lenght_str;

	if (! str)
		return (NULL);
	lenght_str = ft_strlen(str);
	if (start > lenght_str)
		return (ft_strdup(""));
	if (start + len > lenght_str)
		len = lenght_str - start;
	sub_str = ft_calloc(len + 1, sizeof(char));
	if (sub_str)
		ft_strlcpy(sub_str, str + start, len + 1);
	return (sub_str);
}
