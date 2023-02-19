/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 22:58:20 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/17 13:14:01 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void*));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*lst2;

	if (!lst)
		return (NULL);
	lst2 = ft_lstnew(f(lst->content));
	if (!lst2)
		return (NULL);
	newlist = lst2;
	lst = lst->next;
	while (lst)
	{
		lst2->next = ft_lstnew(f(lst->content));
		if (!lst2->next)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		lst = lst->next;
		lst2 = lst2->next;
	}
	return (newlist);
}
