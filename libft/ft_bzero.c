/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:59:41 by dtassel           #+#    #+#             */
/*   Updated: 2022/03/24 13:00:52 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*d;

	d = s;
	while (n > 0)
	{
		*d++ = '\0';
		n--;
	}
}
/*
#include <stdio.h>

int main()
{
	char str[] = "Helloworld";
	printf("\nAvant bzero(): %s", str);
	ft_bzero(str + 2, 2);
	printf("\nApres bzero(): %s", str);
	return (0);
}*/