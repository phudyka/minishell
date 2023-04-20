/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:20:41 by dtassel           #+#    #+#             */
/*   Updated: 2022/05/10 10:48:34 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	count_words(const char *str, char c)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (*str)
	{
		if (*str != c && t == 0)
		{
			t = 1;
			i++;
		}
		else if (*str == c)
			t = 0;
		str++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	strs = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strs)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		while (*s && *s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			strs[i++] = ft_substr(s - len, 0, len);
		}
	}
	strs[i] = NULL;
	return (strs);
}
/*
#include <stdio.h>

int	main()
{
	char strs[] = " Tripouille  42";
	char **tab;
	char c;
	
	c = ' ';
	tab = ft_split(strs, c);
	while (*tab)
	{
		ft_putstr(*tab);
		write (1, "\n", 1);
		tab++;
	}
	return (0);
}*/
