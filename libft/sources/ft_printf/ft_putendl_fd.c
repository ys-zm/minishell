/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 02:47:05 by anonymous         #+#    #+#             */
/*   Updated: 2023/01/18 22:36:19 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_putendl_fd(char *str, int fd)
{
	size_t	tot;

	tot = 0;
	if (str)
	{
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
		tot += 1;
	}
	return (tot + ft_strlen(str));
}
