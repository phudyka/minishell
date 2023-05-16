/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:34:40 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/16 16:01:33 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/parser.h"

static char *parse_arg(t_token **tokens)
{
    char	*arg;

    while (*tokens && (*tokens)->type != IPT && (*tokens)->type != TRC
           && (*tokens)->type != HDC && (*tokens)->type != APP
           && (*tokens)->type != PIP)
    {
        if ((*tokens)->type == CMD)
        {
            if (is_quote((*tokens)->value[0]))
                arg = parse_quotes(&(*tokens)->value);
            else
                arg = ft_strdup((*tokens)->value);
            (*tokens) = (*tokens)->next;
            return (arg);
        }
        (*tokens) = (*tokens)->next;
    }
    return (NULL);
}

char	*master_parser(t_token *tokens)
{
	char	*arg;
	char	*parse;

	while (tokens)
	{
		if (tokens->type == CMD)
			arg = ft_strdup(tokens->value);
		else if (tokens->type == IPT || tokens->type == TRC
				|| tokens->type == HDC || tokens->type == APP)
			arg = NULL;
		else if (tokens->type == PIP)
			arg = parse_pipes(&tokens);
		else
			arg = parse_arg(&tokens);
		if (!arg)
			return (NULL);
		parse = ft_strjoin(arg, " ");
		free(arg);
		tokens = tokens->next;
	}
	return (parse);
}