/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:18:00 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/08 17:16:53y phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int    ft_equal(const char *s)
{
    int    i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

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