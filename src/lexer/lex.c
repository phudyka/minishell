/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:08:29 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/12 09:14:28 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

char    **master_lexer(char *buff)
{
	int     i;
	int     j;
	char    *parse;
	char	**args;

	i = 0;
	j = 0;
	args = (char **)malloc(sizeof(char *) * (ft_strlen(buff) + 1));
	if (!args)
		return (NULL);
	while (buff[j])
	{
		parse = master_parser(&buff);
		if (!parse)
		{
			args[i] = NULL;
			return (args);
		}
		args[i++] = parse;
		while (buff[j] == ' ')
			j++;
		if (metachar(*buff))
			args[i++] = ft_chardup(buff[j++]);
		j++;
	}
	args[i] = NULL;
	return (args);
}