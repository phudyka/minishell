/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:58:28 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/09 11:15:03 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

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
    char *dup = (char *)malloc(sizeof(char) * 2);
    if (!dup)
        return (NULL);
    dup[0] = c;
    dup[1] = '\0';
    return (dup);
}