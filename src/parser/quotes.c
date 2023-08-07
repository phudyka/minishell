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

static void ft_squotes(char c, char *quote_type, char *new, int *j)
{
    if (c == '\'')
        *quote_type = '\0';
    else
        new[(*j)++] = c;
}

static void ft_dquotes(t_token *curr, int *i, int *j, char *quote_type, char *new)
{
    int len;
    char c;

    len = ft_strlen(curr->value);
    c = curr->value[*i + 1];
    if (c == '\"')
        *quote_type = '\0';
    else if (c == '$' && *i < len - 1)
        parse_dollar(i, j, new, curr);
    else
        new[(*j)++] = c;
}

void parse_end(t_token *curr, int j, char quote_type, char* new)
{
    t_shell *shell;

    shell = &g_shell;
    if (quote_type)
    {
        if (j == 0)
        {
            free(new);
            shell->in_qot = 0;
            return ;
        }
        ft_error(QOT, 1);
        free(new);
        shell->in_qot = 1;
        return ;
    }
    if (j == 0 && curr->value[1] == '\0')
    {
        free(new);
        shell->in_qot = 0;
        return ;
    }
    free(curr->value);
    curr->value = new;
    shell->in_qot = 0; 
}

static void ft_sequence(int *i, int *j, char *quote_type, char *new, t_token *curr)
{
    char c;

    c = curr->value[*i + 1];
    if (*quote_type == '\'')
        ft_squotes(c, quote_type, new, j);
    else if (*quote_type == '\"')
        ft_dquotes(curr, i, j, quote_type, new);
    else if (c == '\'')
        *quote_type = '\'';
    else if (c == '\"')
        *quote_type = '\"';
    else
        new[(*j)++] = c;
}

void parse_quotes(t_token *curr)
{
    int i;
    int j;
    int len;
    char quote_type;
    char *new;
    int odd;

    i = -1;
    j = 0;
    odd = 0;
    quote_type = curr->value[0];
    len = ft_strlen(curr->value);
    new = (char *)malloc(len + 1);
    if (!new)
        ft_error(QOT, 1);
    while (++i < len)
    {
        if (curr->value[i] == '\"')
            odd++;
        ft_sequence(&i, &j, &quote_type, new, curr);
    }
    new[j] = '\0';
    if (odd % 2)
    {
        ft_error(QOT, 1);
        free(new);
        return;
    }
    parse_end(curr, j, quote_type, new);
}