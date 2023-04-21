/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:35:48 by dtassel           #+#    #+#             */
/*   Updated: 2023/04/21 16:23:51 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *src, size_t n)
{
    char *dst;
    size_t i;

    dst = (char*)malloc(sizeof(char) * (n + 1));
    if (dst == NULL)
        return (NULL);
    i = 0;
    while (i < n && src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}