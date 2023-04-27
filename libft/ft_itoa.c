/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:44:57 by phudyka           #+#    #+#             */
/*   Updated: 2022/04/18 15:45:20 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	else
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static void	ft_stocknb(long n, char *str, int *i)
{
	if (n > 9)
	{
		ft_stocknb(n / 10, str, i);
		ft_stocknb(n % 10, str, i);
	}
	else
		str[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	int		i;
	long	nbr;
	char	*itoa;

	nbr = n;
	itoa = malloc(sizeof(char) * (ft_nbrlen(nbr) + 1));
	if (!itoa)
		return (NULL);
	i = 0;
	if (nbr < 0)
	{
		itoa[i++] = '-';
		nbr *= -1;
	}
	ft_stocknb(nbr, itoa, &i);
	itoa[i] = '\0';
	return (itoa);
}
