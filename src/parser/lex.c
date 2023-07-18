/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:08:29 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/16 14:12: by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static t_token	*new_token(token type, char *value)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

static void	add_token(t_token **tokens, t_token *new)
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
    t_token *current;
    t_token *next;

    current = tokens;
    while (current)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

static t_token	*tokenizer(char **cmd)
{
	t_token	*tokens;
	
	tokens = NULL;
	while (*cmd)
	{
		if (**cmd == '\'' || **cmd == '\"')
				add_token(&tokens, new_token(QOT, ft_strdup(*cmd)));
		else if (**cmd == '>' || **cmd == '<')
			add_token(&tokens, new_token(RDR, ft_strdup(*cmd)));		
		else if (**cmd == '|')
			add_token(&tokens, new_token(PIP, "|"));
		else
			add_token(&tokens, new_token(STR, ft_strdup(*cmd)));
		if (!*cmd)
			break ;
		cmd++;
	}
	free_array(cmd);
	return (tokens);
}

char	**master_lexer(char *buff)
{
	int		i;
	char	**cmd;
	t_token	*tokens;

	i = 0;
	cmd = ft_split(buff, ' ');
	if (!cmd)
		return (NULL);
	tokens = tokenizer(cmd);
	if (!tokens)
	{
		free_array(cmd);
		return (NULL);
	}
	master_parser(tokens);
	while (tokens)
	{
		cmd[i++] = tokens->value;
		tokens = tokens->next;
	}
	cmd[i] = NULL;
	free_tokens(tokens);
	return (cmd);
}