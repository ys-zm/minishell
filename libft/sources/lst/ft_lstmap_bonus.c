/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:45:38 by anonymous     #+#    #+#                 */
/*   Updated: 2023/03/20 00:29:36 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_obj;
	void	*new_content;

	if (! f || ! del || ! lst)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_obj = ft_lstnew(new_content);
		if (! new_obj)
		{
			del(new_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		else
		{
			ft_lstadd_back(&new_lst, new_obj);
			lst = lst->next;
		}	
	}
	return (new_lst);
}
