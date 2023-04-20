/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:21:38 by dtassel           #+#    #+#             */
/*   Updated: 2022/03/25 12:16:09 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*a;
	const unsigned char	*b;
	size_t				i;

	a = (const unsigned char *)s1;
	b = (const unsigned char *)s2;
	i = 0;
	while (n > 0)
	{
		if (a[i] != b[i])
		{
			return (a[i] - b[i]);
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
	char s1[] = "Hello";
	char s2[] = "HeLlo";

	printf("%d\n", ft_memcmp(s1, s2, 7));
	printf("%d\n", memcmp(s1, s2, 7));
	return (0);
}*/
