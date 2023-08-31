/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:56:39 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/31 01:54:19 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*ft_reassign(t_token **tokens, char *cmd)
{
	char	*temp;

	temp = ft_strdup((*tokens)->value);
	if (!temp)
		return (NULL);
	if (cmd)
		free(cmd);
	return (temp);
}

void	free_recmd(char **cmd, int start, int len)
{
	while (start < len)
	{
		free(cmd[start]);
		cmd[start] = NULL;
		start++;
	}
}

char	*get_trimmed_word(char *start)
{
	char	*end;

	while (*start == ' ')
		start++;
	end = next_word_end(start, 0);
	while (end > start && *(end - 1) == ' ')
		end--;
	return (ft_substr(start, 0, end - start));
}

char	**split_command(t_data *data, int *len)
{
	char	**cmd;
	char	*temp;

	*len = 0;
	temp = ft_strtrim(data->buffer, " ", "\t");
	if (temp)
	{
		free(data->buffer);
		data->buffer = temp;
	}
	cmd = ft_split_buff(data);
	if (!cmd)
		return (NULL);
	while (cmd[*len])
		(*len)++;
	return (cmd);
}
