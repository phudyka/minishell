/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:58:12 by phudyka           #+#    #+#             */
/*   Updated: 2022/04/11 10:14:28 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*s1;
	char		*s2;

	s1 = (char *)src;
	s2 = (char *)dst;
	if (!s1 && !s2)
		return (NULL);
	if (s2 < s1)
		ft_memcpy(s2, s1, len);
	else
		while (--len + 1)
			s2[len] = s1[len];
	return (s2);
}
