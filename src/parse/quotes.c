/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:57:14 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/21 16:34:06 by phudyka          ###   ########.fr       */
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

int ft_quotes(char *cmd)
{
    int i;
    int j;
    int q; 

    q = 0;
    while(*cmd)
    {
        if (*cmd == '\\' && !q)
        {
            if ((*cmd + 1) && !metachar(*cmd + 1))
                cmd++;
        }
        else if (is_quote(*cmd))
        {
            i = -1;
            j = *cmd + 1;
            while(cmd[++i] && cmd[i] != cmd [j])
                j++;
            if (cmd[j] == '\0')
                return(1);
        }
        cmd++;   
    }
    return(0); 
}