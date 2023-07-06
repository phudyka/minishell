/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:17:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/06 12:08:21 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void ft_squote(size_t *j, size_t *i, char *parsed, const char *value)
{
    (*j)++;
    while (value[*j] && !is_squote(value[*j]))
    {
        if (is_meta(value[*j]) || value[*j] == '$')
            (*j)++;
        parsed[(*i)++] = value[*j];
        (*j)++;
    }
    if (is_squote(value[*j]))
        (*j)++;
}

static void ft_dquote(size_t *i, size_t *j, char *parsed, const char *value)
{
    (*j)++;
    while (value[*j] && !is_dquote(value[*j]))
    {
        if (is_meta(value[*j]))
            (*j)++;
        /*if (value[*j] == '$')
            ft_dollar(i, j, parsed, value);*/
        if (value[*j] == '\\' && is_dquote(value[*j + 1]))
        {
            (*j)++;
            if (value[*j])
            {
                parsed[(*i)++] = value[*j];
                (*j)++;
            }
            else
                break;
        }
        else
        {
            parsed[(*i)++] = value[*j];
            (*j)++;
        }
    }
    if (is_dquote(value[*j]))
        (*j)++;
}

static int is_odd(const char *value)
{
    size_t  j;
    size_t  qot;

    j = 0;
    qot = 0;
    while (value[j])
    {
        if (is_squote(value[j]) || is_dquote(value[j]))
            qot++;
        j++;
    }
    return (qot % 2);
}

static char *ft_sequence(size_t len, const char *value)
{
    size_t  i;
    size_t  j;
    char    *parsed;

    i = 0;
    j = 0;
    if (is_odd(value))
        ft_error(QOT, 0);
    parsed = (char *)malloc(sizeof(char) * (len + 1));
    if (!parsed)
        return (NULL);
    while (value[j])
    {
        if (is_squote(value[j]))
            ft_squote(&j, &i, parsed, value);
        else if (is_dquote(value[j]))
            ft_dquote(&i, &j, parsed, value);
        else
            parsed[i++] = value[j++];
    }
    parsed[i] = '\0';
    return (parsed);
}

void    parse_quotes(t_token *tokens)
{
    size_t  len;
    char    *parsed;
    t_token *temp;

    temp = tokens;
    while (temp)
    {
        if (temp->type == QOT && temp->value)
        {
            len = ft_strlen(temp->value);
            parsed = ft_sequence(len, temp->value);
            if (!parsed)
                return;
            free(temp->value);
            temp->value = parsed;
        }
        temp = temp->next;
    }
}