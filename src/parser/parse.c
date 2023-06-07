/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/07 10:29:31 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/parser.h"

/*static int parse_arg(t_token *tokens)
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
}*/

void	master_parser(t_token *token)
{
	while (token)
	{
		/*if (parse_arg(token))
			ft_error(1);
		if (parse_brackets(token))
			ft_error(2);
		if (parse_quotes(token))
			ft_error(3);
		if (parse_pipes(token))	
			ft_error(4);*/
		token = token->next;
	}
}