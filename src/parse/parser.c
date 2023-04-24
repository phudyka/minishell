/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:23:31 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/24 14:42:57 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

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