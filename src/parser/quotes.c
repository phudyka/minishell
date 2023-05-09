/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:58:36 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/09 15:31:07 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int is_quote(char c)
{
    return (c == '\'' || c == '\"');   
}

int	skip_quotes(char **str, char quote)
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
        printf("%c\n", **str);
		if (**str == '\\' && is_quote(*(*str + 1)))
			(*str)++;
		(*str)++;
	}
	arg = ft_strndup(start, *str - start);
	if (**str == *start)
		(*str)++;
	return (arg);
}