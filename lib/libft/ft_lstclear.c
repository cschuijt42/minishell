/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 22:43:14 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/17 12:28:43 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void*));

static void	ft_lst_recursive_remove(t_list *lst, void (*del)(void*))
{
	if ((*lst).next)
		ft_lst_recursive_remove((*lst).next, del);
	ft_lstdelone(lst, del);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (*lst)
		ft_lst_recursive_remove(*lst, del);
	*lst = NULL;
}
