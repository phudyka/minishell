/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:16:16 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/25 17:34:33 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	return (ft_strlen(src));
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	//char src[] = ((void *)0);
	//char dest[10];

	//printf("\nAvant ft_strlcpy : %s", dest);
	printf("%d\n", ft_strlcpy(((void *)0), ((void *)0), 10));
	//printf("\nApres ft_strlcpy : %s", dest);
	
	return (0);
}*/
