/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:38:35 by dtassel           #+#    #+#             */
/*   Updated: 2023/08/31 01:51:50 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set, const char *setb)
{
	unsigned int	len;

	if (!s1 || !set || !setb)
		return (NULL);
	while ((*s1 && ft_strchr(set, *s1)) || ft_strchr(setb, *s1))
		s1++;
	len = ft_strlen(s1);
	while ((ft_strchr(set, s1[len]) || ft_strchr(setb, s1[len])) && len > 0)
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