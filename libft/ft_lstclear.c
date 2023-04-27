/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:01:46 by phudyka           #+#    #+#             */
/*   Updated: 2022/04/14 14:41:54 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buf;

	if (*lst || del)
	{
		while (*lst)
		{
			buf = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = buf;
		}
	}			
}
