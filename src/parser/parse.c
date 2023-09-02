/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/02 06:59:16 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	count_pipes(char *str)
{
	int		pipes;
	int		i;
	char	q;

	pipes = 0;
	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!q)
				q = str[i];
			else if (q == str[i])
				q = 0;
		}
		else if (!q && str[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
}

static int	next_tokens(t_data *data, t_token *curr)
{
	if (!curr || curr->type == PIP)
	{
		ft_error(data->error, PIP, 0);
		return (0);
	}
	return (1);
}

static void	str_token(t_data *data, t_token *curr)
{
	t_token	*next;

	next = curr->next;
	while (next && next->type != PIP)
	{
		if (next->type == STR)
			break ;
		next = next->next;
	}
	if (!next || next->type != STR)
		ft_error(data->error, PIP, 1);
}

static void	parse_pipes(t_data *data, t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == PIP)
		{
			if (!next_tokens(data, tokens->next))
			{
				printf("syntax error near unexpected token `|'\n");
				data->error->status = 2;
				return ;
			}
			else if (prev)
				str_token(data, tokens);
		}
		prev = tokens;
		tokens = tokens->next;
	}
}

void	master_parser(t_data *data, t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == PIP)
			parse_pipes(data, tokens);
		else if (tokens->type == RDR)
			parse_redir(data, tokens);
		tokens = tokens->next;
	}
}
