/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:19:21 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/25 11:52:51 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = dest;
	while (len > 0)
	{
		ptr[i] = c;
		len--;
		i++;
	}
	return (ptr);
}
/*
#include <stdio.h>

int main()
{
	char str[] = "Salut toi";
	printf("\nAvant memset(): %s\n", str);
	ft_memset(str + 5, '/', 1*sizeof(char));
	printf("Après memset(): %s\n", str);
	return (0);
}*/
