/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:15:37 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/12 11: by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

void parse_pipes(t_token *tokens)
{
    t_token *prev;
    t_token *next;
    
	prev = NULL;
	next = NULL;
    while (tokens)
    {
        if (tokens->type == PIP)
        {
            if (!prev || prev->type == PIP ||
                !tokens->next || tokens->next->type == PIP)
				ft_error(PIP, 0);
            next = tokens->next;
            while (next && next->type != PIP)
            {
                if (next->type == CMD)
                    break;
                next = next->next;
            }
            if (!next || next->type != CMD)
				ft_error(PIP, 1);
        }
        prev = tokens;
        tokens = tokens->next;
    }
}


