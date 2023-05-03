/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/03 14:17:23 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	*parse_arg_list(char **str)
{
    char    *arg;

    while (**str == ' ')
        (*str)++;
    if (metachar(**str) || !**str)
        return (NULL);
    if (is_quote(**str))
    {
        arg = parse_quotes(str);
        if (!arg)
            return (NULL);
    }
    else
    {
        arg = ft_strndup(*str, strcspn(*str, " \t|<>"));
            return (NULL);
        *str += ft_strlen(arg);
    }
    return (arg);
}

char    **master_parser(char *buff)
{
    int     i;
    char    *parse;
	char	**args;

	i = 0;
    args = (char **)malloc(sizeof(char *) * (ft_strlen(buff) + 1));
    if (!args)
        return (NULL);
    while (*buff)
	{
		parse = parse_arg_list(&buff);
		if (!parse)
		{
			//free(args);
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