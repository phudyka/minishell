/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:47:55 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/03 14:28:49 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s2[i])
		i++;
	if (i == 0)
		return ((char *)s1);
	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2[0])
		{
			j = 0;
			while (s2[j] && s2[j] == s1[i + j] && i + j < len)
				j++;
			if (s2[j] == 0)
				return ((char *)s1 + i);
		}
		if (++i == len)
			return (0);
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int	main()
{
	char s1[] = "Yo imbess t'es admi vraiment un admin ?";
	char s2[] = "admin";
	size_t len;

	len = -1;
	printf("%s\n", ft_strnstr(s1, s2, len));
	printf("%s\n", strstr(s1, s2));

	return (0);
}*/
