/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptunsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:07:39 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/26 14:26:32 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_nsize(unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_iutoa(unsigned int n)
{
	char			*str;
	unsigned int	len;

	len = ft_nsize(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	while (n != 0)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

int	ft_ptunsigned(unsigned int n)
{
	int		i;
	char	*str;

	i = 0;
	if (n == 0)
		i += write(1, "0", 1);
	else
	{
		str = ft_iutoa(n);
		i += ft_ptstr(str);
		free(str);
	}
	return (i);
}
