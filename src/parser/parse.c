/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/12 09:14:59 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

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
			//printf("%c\n", **str);
            if (**str == '\\' && is_quote(*(*str + 1)))
                (*str)++;
            (*str)++;
        }
    }
    arg = ft_strndup(start, *str - start);
    return (arg);
}

char	*master_parser(char **str)
{
	char	*arg;

	arg = NULL;
	while (**str)
	{
		if (**str == '\'' || **str == '\"')
			arg = parse_quotes(str);
		else if (**str == '|')
			arg = parse_pipes(str);
		else
			arg = parse_arg(str);
		if (!arg)
			return (NULL);
		(*str)++;
		return (arg);
	}
	return (arg);
}