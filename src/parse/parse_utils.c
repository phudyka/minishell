/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:08:41 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/24 11:09:10 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int metachar(char c)
{
    return (c == '|' || c == '<' ||
        c == '>' || c == '&');
}

int is_quote(char c)
{
    return (c == '\'' || c == '\"');   
}

int is_char(char c)
{
    return (c >= 32 && c <= 126 && !metachar(c));
}

char *ft_chardup(char c)
{
    char *str = malloc(sizeof(char) * 2);
    if (!str)
        return (NULL);
    str[0] = c;
    str[1] = '\0';
    return (str);
}