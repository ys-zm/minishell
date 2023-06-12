/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:42:47 by faru              #+#    #+#             */
/*   Updated: 2023/05/27 19:38:45 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim(char *to_trim)
{
	char	*trimmed;
	char	*tmp;
	int32_t	length;

	if (! to_trim)
		return (NULL);
	else if (! *to_trim)
	{
		ft_free(to_trim);
		return (ft_strdup(""));
	}
	tmp = to_trim;
	while (*tmp && ft_isspace(*tmp))
		tmp++;
	if (*tmp == '\0')
	{
		ft_free(to_trim);
		return (ft_strdup(""));
	}
	length = ft_strlen(tmp) - 1;
	while (ft_isspace(tmp[length]))
		length--;
	trimmed = ft_substr(tmp, 0, length + 1);
	ft_free(to_trim);
	return (trimmed);
}
