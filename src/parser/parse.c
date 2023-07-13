/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/13 14:02:15 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

int	find_pipes(t_data *data)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	if (!data->buffer || !data->cmd || !*data->cmd)
		return (0);
	while (data->cmd[i])
	{
		if (ft_strncmp(data->cmd[i], "|", ft_strlen(data->cmd[i])) == 0)
			pipes++;
		i++;
	}
	return (pipes);
}

static void	parse_pipes(t_token *tokens)
{
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	next = NULL;
	while (tokens)
	{
		if (tokens->type == PIP)
		{
			if (!prev || prev->type == PIP 
				|| !tokens->next || tokens->next->type == PIP)
				ft_error(PIP, 0);
			next = tokens->next;
			while (next && next->type != PIP)
			{
				if (next->type == STR)
					break ;
				next = next->next;
			}
			if (!next || next->type != STR)
				ft_error(PIP, 1);
		}
		prev = tokens;
		tokens = tokens->next;
	}
}

void	master_parser(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == STR)
			ft_strdup(tokens->value);
		else if (tokens->type == QOT)
			parse_quotes(tokens);
		else if (tokens->type == PIP)
			parse_pipes(tokens);
		else if (tokens->type == RDR)
			parse_redir(tokens);
		else
			tokens = tokens->next;
		tokens = tokens->next;
	}
}
