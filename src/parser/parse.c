/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/09 15:09:17 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	*parse_arg(t_token *tokens)
{
	char	*arg;

	while (tokens)
	{
		if (tokens->type == CMD)
		{
			arg = ft_strdup(tokens->value);
			tokens = tokens->next;
			return (arg);
		}
		tokens = tokens->next;
	}
	return (NULL);
}

void	master_parser(t_token *tokens)
{

	while (tokens)
	{
		if (tokens->type == CMD)
			ft_strdup(tokens->value);
		else if (tokens->type == QOT)
			parse_quotes(tokens);
		else if (tokens->type == PIP)
			parse_pipes(tokens);
		/*else if (tokens->type == RDR)
			parse_redir(tokens);*/
		else
			parse_arg(tokens);
		tokens = tokens->next;
	}
}