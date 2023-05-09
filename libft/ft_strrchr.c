/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 09:59:06 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/03 14:29:04 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	char	s[] = "tripouille";
	int		c;

	c = 't';
	printf("%s\n", ft_strrchr(s, c));
	printf("%s\n", strrchr(s, c));
	return (0);
}*/
