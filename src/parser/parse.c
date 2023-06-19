/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/19 15:02:45 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	master_parser(t_token *tokens)
{
	while (tokens)
	{
		printf("%s = %d\n",tokens->value, tokens->type);
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