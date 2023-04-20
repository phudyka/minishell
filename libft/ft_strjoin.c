/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:43:06 by dtassel           #+#    #+#             */
/*   Updated: 2023/04/15 06:02:34 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	len;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		((char *)s1)[0] = '\0';
	}
	if (!s1 || !s2)
	{
		free((char *)s1);
		return (0);
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	ft_strlcat(str, s2, len + 1);
	free ((char *)s1);
	return (str);
}
/*
#include <stdio.h>

int	main()
{
	char s1[] = "tripouille";
	char s2[] = "42";

	printf("%s\n", ft_strjoin(s1, s2));
	return (0);
}*/