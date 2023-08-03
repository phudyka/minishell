/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:41:21 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/01 17:09:41 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

t_token *tokenize_command(char **cmd, int cmd_len)
{
	t_token *tokens;

	tokens = NULL;
	tokens = tokenizer(cmd, cmd_len, tokens);
	if (!tokens)
	{
		free_array(cmd);
		return (NULL);
	}
	return (tokens);
}

t_token	*new_token(token type, char *value)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;
	
	if (!tokens || !new)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void free_tokens(t_token *tokens)
{
	t_token	*tmp;

    while (tokens)
    {
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
    }
	tokens = NULL;
}