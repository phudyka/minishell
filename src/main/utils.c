/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:18:00 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/15 11:49:49 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	free_array(char **tab)
{
	int	i;

	i = 0;
	if (!tab[i])
		return ;
	while (tab[i])
		i++;
	while (i >= 0)
		free(tab[i--]);
	free (tab);
}

void	free_data(t_data *data)
{
	free(data->buffer);
	free_array(data->cmd);
	free_array(data->cmd_parts);
	data->buffer = NULL;
	data->cmd = NULL;
	data->cmd_parts = NULL;
}

void	free_buff(t_data *data)
{
	if (data->buffer)
	{
		free(data->buffer);
		data->buffer = NULL;
	}
	if (data->cmd)
	{
		free_array(data->cmd);
		data->cmd = NULL;
	}
}

void	ft_export(char **variable, t_data *data, t_env *current)
{
	while (current)
	{
		if (ft_strncmp(current->var,
				variable[0], ft_strlen(variable[0])) == 0)
		{
			free(current->var);
			free_array(variable);
			current->var = strdup(data->cmd[1]);
			return ;
		}
		current = current->next;
	}
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