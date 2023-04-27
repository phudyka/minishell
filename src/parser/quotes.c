/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:58:36 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/27 11:12:31 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	skip_quotes(char **str, char quote)
{
	(*str)++;
	while (**str && **str != quote)
	{
		if (**str == '\\' && is_quote(*(*str + 1)))
			(*str)++;
		(*str)++;
	}
	if (**str == quote)
		(*str)++;
	return (1);
}

char	*parse_quotes(char **str)
{
	char	*arg;
	char	*start;

	start = ++(*str);
	while (**str && **str != *start)
	{
		if (**str == '\\' && is_quote(*(*str + 1)))
			(*str)++;
		(*str)++;
	}
	arg = ft_strndup(start, *str - start);
	if (**str == *start)
		(*str)++;
	return (arg);
}

char	*parse_arg(char **str)
{
    char	*arg;
    char	*start;

    while (**str == ' ')
        (*str)++;
    if (metachar(**str) || !**str)
        return (NULL);
    start = *str;
    if (is_quote(**str))
    {
        (*str)++;
        skip_quotes(str, *start);
    }
    else
    {
        while (**str && **str != ' ' && !metachar(**str))
        {
            if (**str == '\\' && is_quote(*(*str + 1)))
                (*str)++;
            (*str)++;
        }
    }
    arg = ft_strndup(start, *str - start);
    return (arg);
}