/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:17:26 by dtassel           #+#    #+#             */
/*   Updated: 2023/04/25 10:32:53 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
			i++;
	return (*s1 - *s2);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	//char s1[] = "Tripouille";
	//char s2[] = "Tripouill";

	printf("%d\n", ft_strncmp(((void *)0), ((void *)0), 42));
	//printf("%d\n", strncmp(((void *)0), ((void *)0), 42));
	return(0);
}*/
