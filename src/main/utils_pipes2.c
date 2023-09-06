/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:16:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/06 14:52:58 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

char	*read_line(void)
{
	char	*line;
	size_t	len;

	line = NULL;
	len = 0;
	getline(&line, &len, stdin);
	return (line);
}

void	handle_pipe_execution(t_data *data, t_env *env, int i)
{
	pid_t	pid;
	t_pipe	*pipe_data;

	if (pipe(data->fd) == -1)
		ft_error(data->error, PIP, 0);
	free(data->buffer);
	data->buffer = ft_strdup(data->cmd_parts[i]);
	free_array(data->cmd);
	data->cmd = ft_split(data->buffer, ' ');
	pipe_data = init_pipe_data(data, env, i);
	pid = fork();
	if (pid == -1 || pid == 0)
	{
		if (pid == -1)
			free_data(data);
		if (pid == 0)
			exec_pipe_child(pipe_data);
		data->buffer = NULL;
		ft_error(data->error, PIP, 0);
	}
	handle_parent_process(data);
	free(pipe_data);
}

static int	count_cmd_parts(char **cmd_parts)
{
	int	i;

	i = 0;
	while (cmd_parts && cmd_parts[i])
		i++;
	return (i);
}

static char	**cmd_parts(char **cmd_parts, char *new_command)
{
	int		i;
	char	**new_cmd_parts;

	i = count_cmd_parts(cmd_parts);
	new_cmd_parts = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_cmd_parts)
		return (NULL);
	i = 0;
	while (cmd_parts && cmd_parts[i])
	{
		new_cmd_parts[i] = cmd_parts[i];
		i++;
	}
	new_cmd_parts[i] = ft_strdup(new_command);
	new_cmd_parts[i + 1] = NULL;
	free(cmd_parts);
	return (new_cmd_parts);
}

void	read_next_command(t_data *data)
{
	char	*next_command;
	size_t	len;
	ssize_t	nread;

	next_command = NULL;
	len = 0;
	printf("> ");
	nread = getline(&next_command, &len, stdin);
	if (nread > 0)
	{
		if (next_command[nread - 1] == '\n')
			next_command[nread - 1] = '\0';
		data->cmd_parts = cmd_parts(data->cmd_parts, next_command);
	}
	free(next_command);
}
