/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:23:31 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/21 16:36:24 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static char	*parse_arg(char **str)
{
	char	*arg;
	char	*start;

	while (**str == ' ')
		(*str)++;
	if (metachar(**str) || !**str)
		return (NULL);
	start = *str;
	if (is_quote(*start))
	{
		(*str)++;
		while (**str && **str != *start)
		{
			if (**str == '\\' && (*(*str + 1) == '\'' || *(*str + 1) == '\"' ||
				*(*str + 1) == '\\'))
				(*str)++;
			(*str)++;
		}
	}
	else
	{
		while (**str && **str != ' ' && !metachar(**str))
		{
			if (**str == '\\' && (*(*str + 1) == '\'' || *(*str + 1) == '\"' ||
				*(*str + 1) == '\\'))
				(*str)++;
			(*str)++;
		}
	}
	arg = ft_strndup(start, *str - start);
	return (arg);
}

static int	skip_quotes(char **str, char quote)
{
	(*str)++;
	while (**str && **str != quote)
	{
		if (**str == '\\' && (*(*str + 1) == '\'' || *(*str + 1) == '\"' ||
			*(*str + 1) == '\\'))
			(*str)++;
		(*str)++;
	}
	if (**str == quote)
		(*str)++;
	return (1);
}

static char	*parse_quotes(char **str)
{
	char	*end;
	char	*arg;
	char	*start;

	start = *str;
	skip_quotes(str, **str);
	end = *str;
	arg = ft_strndup(start, end - start);
	return (arg);
}

static char	*parse_arg_list(char **str)
{
	char	*arg;

	arg = NULL;
	while (**str)
	{
		arg = parse_arg(str);
		if (!arg)
			return (NULL);
		if (**str == '\'' || **str == '\"')
			arg = parse_quotes(str);
		if (!arg)
			return (NULL);
		return (arg);
	}
	return (arg);
}

char    **master_parser(char *buff)
{
    int     i;
    char    *parse;
	char	**args;

	i = 0;
    args = (char **)malloc(sizeof(char) * ft_strlen(buff) + 1);
    if (!args)
    {
        return (NULL);
    }
    while (*buff)
	{
		parse = parse_arg_list(&buff);
		if (!parse)
		{
			free(args);
			return (NULL);
		}
		args[i++] = parse;
		while (*buff == ' ')
			buff++;
		if (metachar(*buff))
			args[i++] = ft_chardup(*buff++);
	}
	return (args);
}