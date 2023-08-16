/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:58:28 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/16 02:59:36 by kali             ###   ########.fr       */
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

char	**split_command(t_data *data, int *len)
{
	char	**cmd;

	*len = 0;
	cmd = ft_split_buff(data);
	if (!cmd)
		return (NULL);
	while (cmd[*len])
		(*len)++;
	return (cmd);
}
