/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:17:26 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/25 16:58:14 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (s1[i] && s2[i] && s1[i] == s2[i])
		{
			i++;
		}
		else
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		n--;
	}
	return (*s1 - *s2);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	//char s1[] = "Tripouille";
	//char s2[] = "Tripouill";

	printf("%d\n", ft_strncmp(((void *)0), ((void *)0), 42));
	//printf("%d\n", strncmp(((void *)0), ((void *)0), 42));
	return(0);
}*/
