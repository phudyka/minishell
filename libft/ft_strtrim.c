/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:51:32 by phudyka           #+#    #+#             */
/*   Updated: 2022/06/15 18:26:59 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	left;
	size_t	right;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	str = 0;
	left = 0;
	right = ft_strlen(s1);
	if (s1 != 0 && set != 0)
	{
		while (s1[left] && ft_strchr(set, s1[left]))
			left++;
		while (s1[right - 1] && ft_strchr(set, s1[right - 1]) && right > left)
			right--;
		str = (char *)malloc(sizeof(char) * (right - left + 1));
		if (str)
			ft_strlcpy(str, &s1[left], right - left + 1);
	}
	return (str);
}
