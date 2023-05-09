/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:12:39 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/12 10:45:35 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_nsize(int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i = i + 1;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	i;
	unsigned int	nb;

	if (n == 0)
		return (ft_strdup("0"));
	i = ft_nsize(n);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	str[i] = '\0';
	while (nb != 0)
	{
		str[i - 1] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	return (str);
}
/*
#include <stdio.h>

int	main()
{
	int n;

	n = 0;
	printf("%s\n", ft_itoa(n));
	return (0);
}*/