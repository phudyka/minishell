/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:45:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/10 15:45:34 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*r;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	i = start;
	j = 0;
	if (start + len > ft_strlen(s))
		len = ft_strlen((char *)s) - start;
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	while (s[i] && j < len)
		r[j++] = s[i++];
	r[j] = '\0';
	return (r);
}
/*
#include <stdio.h>

int	main()
{
	char s[] = "0123456789";
	unsigned int start;
	size_t len;

	start = 9;
	len = 10;
	printf("%s\n", ft_substr(s, start, len));
	return (0);
}*/