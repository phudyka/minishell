/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:10:27 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/22 11:58:08 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	is_exit_command(char *cmd_part)
{
	int	j;

	j = 0;
	while (cmd_part[j] && (cmd_part[j] == ' ' || cmd_part[j] == '\t'))
		j++;
	return (!ft_strncmp(cmd_part + j, "exit", 4));
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free (tmp->var);
		free (tmp);
	}
}

void	free_data(t_data *data)
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
	if (data->cmd_parts)
	{
		free_array(data->cmd_parts);
		data->cmd_parts = NULL;
	}
	if (data->path)
	{
		free_array(data->path);
		data->path = NULL;
	}
}

void	builtin_exit(t_data *data)
{
	data->error->exit = TRUE;
}
