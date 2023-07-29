/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/29 12:04:30 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int check_previous_next_tokens(t_token *prev, t_token *curr)
{
	if (!prev || prev->type == PIP || !curr || curr->type == PIP)
	{
		ft_error(PIP, 0);
		return (0);
	}
	return (1);
}

static void find_next_string_token(t_token *curr)
{
	t_token *next;

	next = curr->next;
	while (next && next->type != PIP)
	{
		if (next->type == STR)
			break;
		next = next->next;
	}
	if (!next || next->type != STR)
	{
		ft_error(PIP, 1);
	}
}

static void parse_pipes(t_token *tokens)
{
	t_token *prev;
	
	prev = NULL;
	while (tokens)
	{
		if (tokens->type == PIP)
		{
			if (!check_previous_next_tokens(prev, tokens->next))
				return;
			find_next_string_token(tokens);
		}
		prev = tokens;
		tokens = tokens->next;
	}
}

void	master_parser(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == QOT)
			parse_quotes(tokens);
		else if (tokens->type == PIP)
			parse_pipes(tokens);
		else if (tokens->type == RDR)
			parse_redir(tokens);
		tokens = tokens->next;
	}
}
