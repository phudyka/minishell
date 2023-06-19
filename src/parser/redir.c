/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:22:34 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/19 10:58:12 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	ft_redir_check(t_token *tokens)
{
	if (!tokens || !tokens->next || tokens->next->type != STR)
		ft_putstr_fd("Error! : [Missing arg after redirection operand]\n", 2);
}

void	parse_redir(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == RDR)
		{
			if ((ft_strcmp(tokens->value, "<") == 0) ||
			(ft_strcmp(tokens->value, ">") == 0) ||
			(ft_strcmp(tokens->value, "<<") == 0) ||
			(ft_strcmp(tokens->value, ">>") == 0))
				ft_redir_check(tokens);				
			else
				ft_error(RDR, 0);
		}
		tokens = tokens->next;
	}
}