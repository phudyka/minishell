/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:47:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/09 21:42:49 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int is_valid_quote(const char *s)
{
    char quote_char = 0;
    while (*s)
    {
        if (quote_char == 0 && (*s == '\'' || *s == '"'))
            quote_char = *s;
        else if (*s == quote_char)
            quote_char = 0;
        s++;
    }
    return (quote_char == 0);
}

static const char *next_word_start(const char *s)
{
    while (*s && (*s == ' ' || *s == '\t'))
        s++;
    return s;
}

static const char *next_word_end(const char *s, char quote_char)
{
    if (quote_char)
    {
        while (*s && *s != quote_char)
            s++;
        if (*s == quote_char)
            s++;
    }
    else
    {
        while (*s && *s != ' ' && *s != '\t' && *s != '\'' && *s != '"')
            s++;
    }
    return s;
}

static unsigned int count_words_buff(const char *str)
{
    int i;
    char quote_char;

    i = 0;
    while (*str)
    {
        str = next_word_start(str);
        quote_char = (*str == '\'' || *str == '"') ? *str : 0;
        if (quote_char)
            str++;
        str = next_word_end(str, quote_char);
        if (quote_char && *str == quote_char)
            str++;
        i++;
    }
    return (i);
}

char **ft_split_buff(char const *s)
{
    char        **strs;
    size_t      i;
    const char  *start, *end;
    int         sqot = 0;
    char        quote_char;

    if (!s || !is_valid_quote(s))
    {
        ft_putendl_fd("Error ! [Open Quotes]", STDERR_FILENO);
        return (NULL);
    }

    strs = (char **)malloc(sizeof(char *) * (count_words_buff(s) + 1));
    if (!strs)
        return (NULL);

    i = 0;
    while (*s)
    {
        s = next_word_start(s);
        quote_char = (*s == '\'' || *s == '"') ? *s++ : 0;
        start = s;
        s = next_word_end(s, quote_char);
        end = s;
        if (quote_char == '\'')
            sqot = 1;
        else
            sqot = 0;
        if (start < end)
        {
            char *substr_result = (quote_char && start < end - 1 && *(end - 1) == quote_char) ? ft_substr(start, 0, end - start - 1) : ft_substr(start, 0, end - start);
            if (!substr_result)
            {
                free(strs); // Free the memory allocated for strs
                return NULL;
            }
            strs[i++] = ft_dollar(substr_result, sqot);
            free(substr_result);
        }
    }
    strs[i] = NULL;
    return (strs);
}
