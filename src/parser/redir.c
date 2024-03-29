/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:32:23 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/11 11:40:11 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	is_only_spaces_or_tabs(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

static int	is_str_type(t_token *token)
{
	return (token && token->type == STR);
}

static void	handle_error(t_data *data, int condition)
{
	if (condition)
	{
		ft_error(data->error, RDR, 0);
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

int	parse_redir(t_data *data, t_token *tokens)
{
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == RDR)
		{
			next = tokens->next;
			if (!is_str_type(next))
			{
				handle_error(data, !is_str_type(prev));
				printf("syntax error near unexpected token `newline'\n");
				return (1);
			}
			else if (prev != NULL)
				set_redir_file(prev, tokens, next);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
}
