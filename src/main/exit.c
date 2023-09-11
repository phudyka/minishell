/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:10:27 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/11 11:38:22 by phudyka          ###   ########.fr       */
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

void	handle_that_shit(char *next_command, t_data *data)
{
	ssize_t	nread;

	nread = ft_strlen(next_command);
	if (next_command[nread - 1] == '\n')
		next_command[nread - 1] = '\0';
	data->cmd_parts = cmd_parts(data->cmd_parts, next_command);
	if (next_command)
	{
		free(next_command);
		next_command = NULL;
	}
}

void	builtin_exit(t_data *data)
{
	data->error->exit = TRUE;
}
