/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:12:49 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/12 10:55:18 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;
	size_t	memlen;

	if (count == __SIZE_MAX__ && size == __SIZE_MAX__)
		return (NULL);
	memlen = count * size;
	a = malloc(memlen);
	if (!a)
		return (0);
	ft_memset(a, 0, memlen);
	return (a);
}
/*
#include <stdio.h>

int	main()
{
	size_t a;
	size_t b;

	a = __SIZE_MAX__;
	b = __SIZE_MAX__;

	printf("%p\n", ft_calloc(a, b));
	return (0);
}*/