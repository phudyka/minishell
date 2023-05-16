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

#include "../../include/lexer.h"

static t_token	*new_token(token type, char *value)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

static void	add_token(t_token *tokens, t_token *new)
{
	t_token	*tmp;
	
	if (!tokens || !new)
		return ;
	if (!tokens)
	{
		tokens = new;
		return ;
	}
	tmp = tokens;
	while (tmp->next)
	{
		tmp = tmp->next;
		tmp->next = new;
	}
}

static void free_tokens(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return ;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	tmp = NULL;
}

static t_token	*tokenizer(char **cmd)
{
	t_token *tokens;
	
	tokens = NULL;
	while (*cmd)
	{
		if (ft_strcmp(*cmd, "<") == 0)
			add_token(tokens, new_token(IPT, NULL));
		else if (ft_strcmp(*cmd, ">") == 0)
			add_token(tokens, new_token(TRC, NULL));
		else if (ft_strcmp(*cmd, "<<") == 0)
			add_token(tokens, new_token(HDC, NULL));
		else if (ft_strcmp(*cmd, ">>") == 0)
			add_token(tokens, new_token(APP, NULL));
		else if (ft_strcmp(*cmd, "|") == 0)
			add_token(tokens, new_token(PIP, NULL));
		else
			add_token(tokens, new_token(CMD, ft_strdup(*cmd)));
		if (!cmd || !tokens)
			break ;
		cmd++;
	}
	return (tokens);
}

char	**master_lexer(char *buff)
{
    int		i;
	//char	**parse;
	char	**args;
    t_token	*tokens;
    
    i = 0;
    args = (char **)malloc(sizeof(char *) * (ft_strlen(buff) + 1));
    if (!args)
        return (NULL);
    tokens = tokenizer(&buff);
	while (tokens)
	{
		if (tokens->type == CMD)
			args[i++] = ft_strdup(tokens->value);
        else
			args[i++] = ft_chardup(tokens->type);
        tokens = tokens->next;
    }
    args[i] = NULL;
	//parse = master_parser(args, tokens);
    free_tokens(tokens);
    return (args);
}
