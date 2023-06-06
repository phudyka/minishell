/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/06 16:30:57 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/parser.h"

static int parse_arg(t_token *tokens)
{
	while (tokens && tokens->type != IPT && tokens->type != TRC
			&& tokens->type != HDC && tokens->type != APP
			&& tokens->type != PIP)
	{
		if (tokens->type == CMD)
		{
			tokens = tokens->next;
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

void	master_parser(t_token *token)
{
	while (token)
	{
		if (parse_arg(token))
			ft_error(IPT);
		if (parse_brackets(token))
			ft_error(RPR);
		if (parse_pipes(token))	
			ft_error(PIP);
		token = token->next;
	}
}