/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthexat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:39:42 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/26 14:25:27 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_counter_hext(unsigned	int num)
{
	int	counter;

	counter = 0;
	while (num)
	{
		counter++;
		num = num / 16;
	}
	return (counter);
}

int	ft_pthexat(unsigned int num)
{
	if (num == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	if (num >= 16)
	{
		ft_pthexat(num / 16);
		ft_pthexat(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'A'), 1);
	}
	return (ft_counter_hext(num));
}
