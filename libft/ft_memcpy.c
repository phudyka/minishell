/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:13:27 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/25 17:33:17 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*a;
	char	*b;
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	a = (char *)src;
	b = (char *)dest;
	while (i < n)
	{
		b[i] = a[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	//char src[] = "Helloworld!";
	//char dest[] = "Salut";

	//printf("\nAvant ft_Memcpy : %s", dest);
	//ft_memcpy(dest, src, 10);
	//printf("\nAprès ft_Memcpy : %s", dest);
	ft_memcpy(((void *)0), ((void *)0), 10);
	//printf("\nAprès Memcpy : %s", dest);
	return (0);
}*/
