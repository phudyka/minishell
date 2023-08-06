/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:18:00 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/06 15:55:52 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void free_array(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return;
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

void	free_buff(t_data *data)
{
	free(data->buffer);
	free_array(data->cmd);
	data->cmd = NULL;
	data->buffer = NULL;
}

static unsigned int	count_words_buff(const char *str)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (*str)
	{
		if ((*str != ' ') && t == 0)
		{
			t = 1;
			i++;
		}
		else if (*str == ' ')
			t = 0;
		str++;
	}
	return (i);
}

char	**ft_split_buff(char const *s)
{
	char	**strs;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	strs = (char **)malloc(sizeof(char *) * (count_words_buff(s) + 1));
	if (!strs)
		return (NULL);
	while (*s)
	{
		if (*s == ' ' || *s == '\t')
			s++;
		while (*s && *s != ' ')
		{
			len = 0;
			while (*s && (*s != ' ') && ++len)
				s++;
			strs[i++] = ft_substr(s - len, 0, len);
		}
	}
	strs[i] = NULL;
	return (strs);
}