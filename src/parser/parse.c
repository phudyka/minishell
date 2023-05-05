/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/05 13:52:39 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	*master_lexer(char **str)
{
	char	*arg;

	arg = NULL;
	while (**str)
	{
		arg = parse_arg(str);
		if (!arg)
			return (NULL);
		if (is_quote(**str))
			arg = parse_quotes(str);
		if (**str == '|')
			arg = parse_pipes(str);
		//if (**str == '')
		if (!arg)
			return (NULL);
		(*str)++;
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
    args = (char **)malloc(sizeof(char *) * (ft_strlen(buff) + 1));
    if (!args)
        return (NULL);
    while (*buff)
	{
		parse = master_lexer(&buff);
		if (!parse)
		{
			free_ttab(args);
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