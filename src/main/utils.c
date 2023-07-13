/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:18:00 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/13 10:58:09 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	print_list(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}

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

char	*allocatenate(char *cmd, char *path)
{
	int		len;
	char	*exec;

	len = ft_strlen(path) + ft_strlen(cmd);
	exec = malloc(sizeof(char) * (len + 1));
	if (!exec)
		return (NULL);
	ft_strlcpy(exec, path, ft_strlen(path) + 1);
	ft_strlcat(exec, cmd, len + 1);
	return (exec);
}
