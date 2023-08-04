/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:17:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/04 17:43:45 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void ft_squote(size_t *j, size_t *i, char *parsed, const char *str)
{
    (*j)++;
    while (str[*j] && !is_squote(str[*j]))
    {
        parsed[(*i)++] = str[*j];
        (*j)++;
    }
    if (is_squote(str[*j]))
        (*j)++;
}

static void ft_dquote(size_t *i, size_t *j, char *parsed, const char *str)
{
    (*j)++;
    while (str[*j] && !is_dquote(str[*j]))
    {
        // if (str[*j] == '$' && str[*j - 1] != '\\')
        //     master_expander('$', parsed);
        if (str[*j] == '\\' && is_dquote(str[*j + 1]))
        {
            (*j)++;
            if (str[*j])
            {
                parsed[(*i)++] = str[*j];
                (*j)++;
            }
            else
                break;
        }
        else
        {
            parsed[(*i)++] = str[*j];
            (*j)++;
        }
    }
    if (is_dquote(str[*j]))
        (*j)++;
}

static int is_odd(const char *str)
{
    size_t  j;
    size_t  sqot;
    size_t  dqot;

    j = 0;
    sqot = 0;
    dqot = 0;
    while (str[j])
    {
        if (is_squote(str[j]))
            sqot++;
        if (is_dquote(str[j]))
            dqot++;
        j++;
    }
    if (dqot % 2 | sqot % 2)
        return (1);
    return (0);
}

static char *ft_sequence(size_t len, const char *str)
{
    size_t  i;
    size_t  j;
    char    *parsed;

    i = 0;
    j = 0;
    if (is_odd(str))
    {
        ft_error(QOT, 1);
        return (NULL);
    }
    parsed = (char *)malloc(sizeof(char) * (len + 1));
    if (!parsed)
        return (NULL);
    while (str[j])
    {
        if (is_squote(str[j]))
            ft_squote(&j, &i, parsed, str);
        else if (is_dquote(str[j]))
            ft_dquote(&i, &j, parsed, str);
        else if (str[j] == ' ')
        {
            parsed[i++] = str[j++];
            while (str[j] && str[j] == ' ')
                j++;
        }
        else
            parsed[i++] = str[j++];
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
                return ;
            free(temp->value);
            temp->value = parsed;
        }
        temp = temp->next;
    }
}