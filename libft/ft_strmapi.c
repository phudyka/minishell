/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:26:19 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/01 11:46:04 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = ft_strdup(s);
	if (!str || !s || !f)
		return (NULL);
	while (str[i])
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}
/*
#include <stdio.h>

int main()
{
	char	*str;
	char	(*f)(unsigned int, char);

	str = "Hello";
	f = ft_test;
	printf("%s\n", ft_strmapi(str, (*f)));
	return (0);
}*/