/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:18:00 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/04 16:46:28 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void free_array(char **tab)
{
    int i;

    i = 0;
    if (tab == NULL)
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
	ft_strlcat(exe, cmd, len + 1);
	return (exe);
}

void	free_buff(t_data *data)
{
	free(data->buffer);
	free_array(data->cmd);
	data->cmd = NULL;
	data->buffer = NULL;
}