/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:35:48 by dtassel           #+#    #+#             */
/*   Updated: 2022/05/10 10:05:42 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*b;
	size_t	c;

	c = ft_strlen(s) + 1;
	b = malloc(sizeof(char) * c);
	if (b == 0)
	{
		return (NULL);
	}
	b = ft_memcpy(b, s, c);
	return (b);
}
/*
#include <stdio.h>

int	main()
{
	const char s[] = "Hey ça fonctionne";

	printf("%s\n", ft_strdup(s));
	return (0);
}*/