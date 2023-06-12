/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:45:28 by anonymous     #+#    #+#                 */
/*   Updated: 2023/03/20 00:29:18 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (! lst || ! f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
