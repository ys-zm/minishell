/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raise_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 05:20:28 by fra           #+#    #+#                 */
/*   Updated: 2023/02/23 22:54:53 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_raise_error(char *text, int end)
{
	ft_putstr_fd(text, 2);
	ft_putchar_fd('\n', 2);
	if (end)
		exit(EXIT_FAILURE);
	else
		return (NULL);
}
