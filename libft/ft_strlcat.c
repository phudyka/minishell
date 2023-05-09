/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:44:18 by dtassel           #+#    #+#             */
/*   Updated: 2022/05/09 12:16:37 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;
	size_t	len_r;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	len_r = len_dest;
	i = 0;
	if (n <= len_dest)
		return (n + len_src);
	while (len_dest < n - 1 && src[i])
	{
		dest[len_dest] = src[i];
		i++;
		len_dest++;
	}
	dest[len_dest] = '\0';
	return (len_r + len_src);
}
/*
#include <stdio.h>

int main()
{
    char src[] = "AAAAAAAAA";
    char dest[] = "B";

    printf("%ld", ft_strlcat(dest, src, -1));
    printf("\n%s", dest);
    return (0);
}*/