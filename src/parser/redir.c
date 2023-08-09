/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:32:23 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/09 21:32:52 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	is_str_type(t_token *token)
{
	return (token && token->type == STR);
}

static void	handle_error(int condition)
{
	if (condition)
	{
		ft_error(RDR, 0);
		return ;
	}
}

static void	set_redir_file(t_token *prev, t_token *curr, t_token *next)
{
	prev->redir = curr->value;
	prev->file = next->value;
	curr->type = STR;
	next->type = STR;
}

void	parse_redir(t_token *tokens)
{
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == RDR)
		{
			next = tokens->next;
			if (!is_str_type(prev) || !is_str_type(next))
			{
				handle_error(!is_str_type(prev));
				return ;
			}
			set_redir_file(prev, tokens, next);
		}
		prev = tokens;
		tokens = tokens->next;
	}
}
