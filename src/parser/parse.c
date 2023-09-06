/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/06 14:29:31 by phudyka          ###   ########.fr       */
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

static int	next_tokens(t_data *data, t_token *prev, t_token *curr)
{
	if (!prev || prev->type == PIP || !curr || curr->type == PIP)
	{
		ft_error(data->error, PIP, 0);
		return (0);
	}
	return (1);
}

static void	parse_pipes(t_data *data, t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == PIP)
		{
			if (!next_tokens(data, prev, tokens->next) && tokens->next)
			{
				printf("syntax error near unexpected token`|'\n");
				data->error->status = 2;
				return ;
			}
		}
		prev = tokens;
		tokens = tokens->next;
	}
}

int	master_parser(t_data *data, t_token *tokens)
{
	parse_pipes(data, tokens);
	while (tokens)
	{
		if (tokens->type == RDR)
			if (parse_redir(data, tokens) != 0)
				return (1);
		tokens = tokens->next;
	}
	return (0);
}
