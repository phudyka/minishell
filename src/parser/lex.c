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
	token->value = ft_strdup(value);
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

static t_token	*tokenizer(char **cmd, int size)
{
	t_token	*tokens;
	t_token *new_token_instance;
	int		i;
	
	i = 0;
	tokens = NULL;
	while (i < size)
	{
		if (cmd[i][0] == '\'' || cmd[i][0] == '\"')
			new_token_instance = new_token(QOT, cmd[i]);
		else if (cmd[i][0] == '>' || cmd[i][0] == '<')
			new_token_instance = new_token(RDR, cmd[i]);		
		else if (cmd[i][0] == '|')
			new_token_instance = new_token(PIP, "|");
		else if (cmd[i][0] == '\\' || cmd[i][0] == ';')
			i++;
		else
			new_token_instance = new_token(STR, cmd[i]);

		if (!new_token_instance)
		{
			free_tokens(tokens);
			return (NULL);
		}
		add_token(&tokens, new_token_instance);
		if (!cmd[i])
			break ;
		i++;
	}
	return (tokens);
}

static char	**split_command(char *buff, int *cmd_len)
{
	char **cmd;

	cmd = ft_split(buff, ' ');
	if (!cmd)
		return (NULL);
	*cmd_len = 0;
	while (cmd[*cmd_len])
		(*cmd_len)++;
	return cmd;
}

static t_token *tokenize_command(char **cmd, int cmd_len)
{
	t_token *tokens;

	tokens = tokenizer(cmd, cmd_len);
	if (!tokens)
	{
		free_array(cmd);
		return (NULL);
	}
	return tokens;
}

static char **reassign_cmd(t_token **tokens, char **cmd, int cmd_len)
{
	int i;
	char *temp;

	i = 0;
	while (i < cmd_len && *tokens)
	{
		free(cmd[i]);
		temp = ft_strdup((*tokens)->value);
		if (!temp)
		{
			free_array(cmd);
			return (NULL);
		}
		cmd[i] = temp;
		*tokens = (*tokens)->next;
		i++;
	}
	cmd[i] = NULL;
	return cmd;
}

char **master_lexer(char *buff)
{
	char	**cmd;
	t_token	*tokens;
	t_token	*start;
	int		cmd_len;

	cmd = split_command(buff, &cmd_len);
	if (!cmd)
		return (NULL);
	tokens = tokenize_command(cmd, cmd_len);
	if (!tokens)
	{
		free_array(cmd);
		return (NULL);
	}
	start = tokens;
	master_parser(tokens);
	cmd = reassign_cmd(&tokens, cmd, cmd_len);
	if (!cmd)
	{
		free_tokens(start);
		free_array(cmd);
		return (NULL);
	}
	free_tokens(start);
	return cmd;
}
