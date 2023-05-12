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

static char	*parse_pipes(t_token **tokens)
{
	char	*cmd1;
	char	*cmd2;

	cmd1 = NULL;
	cmd2 = NULL;
	while (*tokens)
	{
		if ((*tokens)->type == CMD && !cmd1)
			cmd1 = ft_strdup((*tokens)->value);
		else if ((*tokens)->type == PIP)
			break ;
		*tokens = (*tokens)->next;
	}
	if (*tokens)
		*tokens = (*tokens)->next;
	while (*tokens)
	{
		if ((*tokens)->type == CMD && !cmd2)
			cmd2 = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
	}
	if (cmd1 && cmd2)
		return (ft_strjoin(ft_strjoin(cmd1, " | "), cmd2));
	return (cmd1);
}