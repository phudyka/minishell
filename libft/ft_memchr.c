/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:44:52 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/03 13:50:27 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*a;
	size_t		i;

	a = (const char *)s;
	i = 0;
	while (n > 0)
	{
		if (a[i] == (char)c)
		{
			return ((void *)(s + i));
		}
		i++;
		n--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	char s[] = "Hello";
	int	c;

	c = 'l';
	printf("%p\n", ft_memchr(s, c, 5));
	printf("%p\n", memchr(s, c, 5));
	return (0);
}*/