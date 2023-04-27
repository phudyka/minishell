/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:01:50 by phudyka           #+#    #+#             */
/*   Updated: 2022/04/12 11:43:12 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dst;

	j = 0;
	if (!s)
		return (NULL);
	if (start < ft_strlen(s))
		j = ft_strlen(s) - start;
	if (j > len)
		j = len;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	dst = (char *)malloc(sizeof(char) * j + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
