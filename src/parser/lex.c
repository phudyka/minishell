/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:37:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/31 15:41:34 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

t_token	*create_token(char *cmd)
{
	t_token	*new_token_instance;

	if (cmd[0] == '\'' || cmd[0] == '\"')
		new_token_instance = new_token(QOT, cmd);
	else if ((ft_strcmp(cmd, ">") == 0) || (ft_strcmp(cmd, "<") == 0)
		|| (ft_strcmp(cmd, ">>") == 0))
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
			break ;
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

static char	**reassign_cmd(t_token **tokens, char **cmd, int len)
{
	int	i;

	i = 0;
	while (i < len && *tokens)
	{
		if (!ft_strcmp((*tokens)->value, cmd[i]))
			cmd[i] = ft_reassign(tokens, cmd[i]);
		else
		{
			cmd[i] = ft_reassign(tokens, cmd[i]);
			if (!cmd[i])
			{
				free_array(cmd);
				return (NULL);
			}
		}
		*tokens = (*tokens)->next;
		i++;
	}
	free_recmd(cmd, i, len);
	return (cmd);
}

char	**master_lexer(t_data *data)
{
	int		len;
	char	**cmd;
	t_token	*tokens;
	t_token	*start;

	cmd = split_command(data, &len);
	if (!cmd)
		return (NULL);
	tokens = tokenize_command(cmd, len);
	if (!tokens)
	{
		free_array(cmd);
		return (NULL);
	}
	start = tokens;
	master_parser(data, tokens);
	cmd = reassign_cmd(&tokens, cmd, len);
	free_tokens(start);
	if (!cmd)
	{
		free_array(cmd);
		return (NULL);
	}
	free_tokens(tokens);
	return (cmd);
}
