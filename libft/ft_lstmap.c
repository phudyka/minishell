/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:03:05 by phudyka           #+#    #+#             */
/*   Updated: 2022/04/15 17:19:04 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newmap;

	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		ft_lstiter(lst, f(lst->content));
		newmap = lst->next;
	}
	if (del)
	{
		newmap = lst->next;
		ft_lstclear(&lst, del);
		return (newmap);
	}
	return (newmap);
}
