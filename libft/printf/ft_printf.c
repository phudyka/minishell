/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:06:39 by dtassel           #+#    #+#             */
/*   Updated: 2022/04/26 15:43:19 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_format(va_list args, const char c)
{
	int	format;

	format = 0;
	if (c == 'c')
		format += ft_ptchar(va_arg(args, int));
	else if (c == 's')
		format += ft_ptstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		format += ft_ptnbr(va_arg(args, int));
	else if (c == 'u')
		format += ft_ptunsigned(va_arg(args, unsigned int));
	else if (c == '%')
		format += ft_ptchar(c);
	else if (c == 'p')
		format += ft_pt_ptr(va_arg(args, unsigned long));
	else if (c == 'x')
		format += ft_pthexal(va_arg(args, unsigned int));
	else if (c == 'X')
		format += ft_pthexat(va_arg(args, unsigned int));
	return (format);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		format;

	i = 0;
	format = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			format += ft_format(args, str[i + 1]);
			i++;
		}
		else
			format += ft_ptchar(str[i]);
		i++;
	}
	va_end(args);
	return (format);
}
/*
#include <stdio.h>

int	main(void)
{
	//char			c;
	//char			*str;
	//int				d;
	//unsigned int	u;
	//int h;
	void *p;

	p = 0;
	//h = 789456444;
	//u = 0;
	//d = -42;
	//str = "";
	//c = 'H';
	ft_printf(" %p ", p);
	printf(" %p ", p);
	return (0);
}*/
