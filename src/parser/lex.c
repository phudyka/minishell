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

static t_token	*create_token(char *cmd)
{
    t_token *new_token_instance;
    
    if (cmd[0] == '\'' || cmd[0] == '\"')
        new_token_instance = new_token(QOT, cmd);
    else if (ft_strcmp(cmd, ">") == 0 ||
		ft_strcmp(cmd, "<") == 0 || ft_strcmp(cmd, ">>") == 0)
        new_token_instance = new_token(RDR, cmd);		
    else if (ft_strcmp(cmd, "|") == 0)
        new_token_instance = new_token(PIP, "|");
    else
        new_token_instance = new_token(STR, cmd);
    return (new_token_instance);
}

t_token	*tokenizer(char **cmd, int size, t_token *tokens)
{
    int		i;
    t_token	*new_token_instance;
	
	i = -1;
    while (++i < size)
	{
        if (!cmd[i])
            break;     
        new_token_instance = create_token(cmd[i]);
        if (!new_token_instance)
		{
            free_tokens(tokens);
            return (NULL);
        }      
        add_token(&tokens, new_token_instance);        
    }
    return (tokens);
}

static char	**split_command(char *buff, int *cmd_len)
{
	char **cmd;

	cmd = ft_split_buff(buff);
	if (!cmd)
		return (NULL);
	*cmd_len = 0;
	while (cmd[*cmd_len])
		(*cmd_len)++;
	return (cmd);
}

static char **reassign_cmd(t_token **tokens, char **cmd, int cmd_len)
{
	int i;
	char *temp;

	i = 0;
	while (i < cmd_len && *tokens)
	{
        if ((*tokens)->value == cmd[i])
            temp = cmd[i];
        else
		{
            temp = ft_strdup((*tokens)->value);
            if (!temp)
            {
                free_array(cmd);
                return (NULL);
            }
            if (cmd[i])
                free(cmd[i]);
            cmd[i] = temp;
        }
		*tokens = (*tokens)->next;
		i++;
	}
	while (i < cmd_len)
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	return (cmd);
}

char **master_lexer(char *buff)
{
	int		cmd_len;
	char	**cmd;
	t_token	*tokens;
	t_token	*start;

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
	return (cmd);
}