/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:38:35 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/03 15:27:54 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	unsigned int	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[len]) && len > 0)
		len--;
	return (ft_substr(s1, 0, len + 1));
}
/*
#include <stdio.h>

int	main()
{
	char s1[] = "Salut";
	char set[] = "St";

	printf("%s\n", ft_strtrim(s1, set));
	return (0);
}*/