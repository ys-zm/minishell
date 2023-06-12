/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 01:45:24 by anonymous         #+#    #+#             */
/*   Updated: 2023/05/27 19:39:20 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	len_substr(char const *str, char char_split)
{
	size_t	length;

	length = 0;
	while (*str && *str++ != char_split)
		length++;
	return (length);
}

char	**ft_split(char const *str, char split, bool trim)
{
	char	**matrix;
	char	*sub_str;
	size_t	index;

	index = 0;
	if (! str)
		return (NULL);
	matrix = ft_calloc((ft_n_substr(str, split) + 1), sizeof(char *));
	if (! matrix)
		return (NULL);
	while (matrix && *str)
	{
		if (*str != split)
		{
			sub_str = ft_substr(str, 0, len_substr(str, split));
			if (trim)
				sub_str = ft_trim(sub_str);
			if (! sub_str)
				return (ft_free_double((void **) matrix, index));
			matrix[index++] = sub_str;
			str += ft_strlen(sub_str) - 1;
		}
		str++;
	}
	return (matrix);
}
