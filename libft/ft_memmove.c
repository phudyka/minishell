/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:39:02 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/25 17:34:25 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*a;
	unsigned char		*b;

	i = 0;
	a = src;
	b = dest;
	if (!dest && !src)
		return (0);
	if (b > a)
	{
		while (i < n)
		{
			b[n - 1] = a[n - 1];
			n--;
		}
	}
	while (i < n)
	{
		b[i] = a[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>

int main()
{
	char src[] = "Helloworld";
	char dest[] = "Salutmonde!";

	printf("\nAvant ft_memmove : %s", dest);
	ft_memmove(dest, src, 10);
	printf("\nAprès ft_memmove : %s", dest);
	return (0);
}*/
