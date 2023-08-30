/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:18:00 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/30 08:05:12 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	ft_equal(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	free_array(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*allocatenate(char *cmd, char *path)
{
	int		len;
	char	*exe;

	len = ft_strlen(path) + ft_strlen(cmd);
	exe = (char *)malloc(sizeof(char) * (len + 1));
	if (!exe)
		return (NULL);
	ft_strlcpy(exe, path, ft_strlen(path) + 1);
	ft_strlcat(exe, cmd, len + ft_strlen(cmd) + 1);
	return (exe);
}

void	process_words(char *s, char **strs, size_t *i, char **temp)
{
	char	*merged;

	if (*temp)
	{
		merged = ft_strjoin(*temp, strs[*i - 1]);
		free(strs[*i - 1]);
		strs[*i - 1] = merged;
		*temp = NULL;
	}
	if (*s && *s != ' ' && *s != '\t')
	{
		*temp = strs[*i - 1];
		strs[*i - 1] = NULL;
		(*i)--;
	}
}

void	free_buff(t_data *data)
{
	free(data->buffer);
	free_array(data->cmd);
	data->cmd = NULL;
	data->buffer = NULL;
}
