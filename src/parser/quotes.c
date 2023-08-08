/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:17:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/07 11:56:12 phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void parse_quotes(t_token *tokens)
{
    int     i;
    int     j;
    int     len;
    char    *parsed;

    i = 0;
    j = 0;
    len = ft_strlen(tokens->value); 
    parsed = (char *)malloc(sizeof(char) * (len + 1));
    if(!parsed)
    {
        perror("malloc");
        return ;
    }
    while (i < len)
    {
        if (tokens->value[i] == '"')
        {
            i++; 
            while (i < len && tokens->value[i] != '"')
            {
                parsed[j++] = tokens->value[i++];
            }
            if (i < len && tokens->value[i] == '"') 
                i++;
        }
        else
        {
            parsed[j++] = tokens->value[i++];
        }
    }
    parsed[j] = '\0';
    free(tokens->value);
    tokens->value = parsed;
}