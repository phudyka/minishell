/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/09 11:30:18 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char	*parse_arg_list(char **str)
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
			args[i] = NULL;
			return (args);
		}
		args[i++] = parse;
		while (*buff == ' ')
			buff++;
		if (metachar(*buff))
			args[i++] = ft_chardup(*buff++);
	}
	args[i] = NULL;
	return (args);
}
