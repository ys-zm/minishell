/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 18:35:45 by faru          #+#    #+#                 */
/*   Updated: 2023/02/23 18:38:25 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_bzero(void *to_modify, size_t no_times)
{
	char	*chr_ptr;

	chr_ptr = (char *) to_modify;
	while (no_times--)
		*chr_ptr++ = '\0';
}
