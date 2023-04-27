/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:23:42 by phudyka           #+#    #+#             */
/*   Updated: 2022/04/14 14:41:08 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nelem;

	nelem = malloc(sizeof(t_list));
	if (!nelem)
		return (NULL);
	nelem->content = content;
	nelem->next = NULL;
	return (nelem);
}
