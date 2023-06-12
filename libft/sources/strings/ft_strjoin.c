/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:59:40 by faru              #+#    #+#             */
/*   Updated: 2023/05/31 23:02:06 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char *s1, char *s2, const char *join_str, bool free_stuff)
{
	uint32_t	s1_len;
	uint32_t	s2_len;
	uint32_t	tot_length;
	char		*joined;

	if ((s1 == NULL) && (s2 == NULL))
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tot_length = s1_len + s2_len + ft_strlen(join_str) * (s1 != NULL);
	joined = ft_calloc(tot_length + 1, sizeof(char));
	if (joined)
	{
		ft_strlcpy(joined, s1, s1_len + 1);
		if (s1)
			ft_strlcpy(joined + s1_len, join_str, ft_strlen(join_str) + 1);
		ft_strlcpy(joined + s1_len + ft_strlen(join_str) * (s1 != NULL), s2, s2_len + 1);
	}
	if (free_stuff)
	{
		ft_free(s1);
		ft_free(s2);
	}
	return (joined);
}
