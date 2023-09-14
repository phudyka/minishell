/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:22:34 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/14 08:11:13 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

int	handle_append_redirection(t_data *data, int *i)
{
	int	fd;

	if (is_next_token_invalid(data, *i))
		return (-1);
	fd = open(data->cmd[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->cmd[*i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->error->status = 1;
		free_data(data);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(data->cmd[*i]);
	free(data->cmd[*i + 1]);
	data->cmd[*i] = NULL;
	data->cmd[*i + 1] = NULL;
	(*i) += 2;
	return (1);
}

void	process_input(int *fd, char *delimiter)
{
	char	*line;
	size_t	len;
	ssize_t	read;

	line = NULL;
	len = 0;
	write(1, "> ", 2);
	read = getline(&line, &len, stdin);
	while (read != -1)
	{
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		write(1, "> ", 2);
		free(line);
		line = NULL;
		read = getline(&line, &len, stdin);
	}
}

int	handle_heredoc_redirection(t_data *data, int *i)
{
	int		fd[2];
	char	*delimiter;

	if (is_next_token_invalid(data, *i))
		return (-1);
	delimiter = data->cmd[*i + 1];
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Error: pipe creation failed.\n", 2);
		data->error->status = 2;
		free_data(data);
		return (-1);
	}
	process_input(fd, delimiter);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	free(data->cmd[*i]);
	free(data->cmd[*i + 1]);
	data->cmd[*i] = NULL;
	data->cmd[*i + 1] = NULL;
	(*i) += 2;
	return (1);
}

int	execute_redirection(t_data *data, int *i, char *token)
{
	if (ft_strcmp(token, ">") == 0)
		return (handle_output_redirection(data, i));
	else if (ft_strcmp(token, "<") == 0)
		return (handle_input_redirection(data, i));
	else if (ft_strcmp(token, ">>") == 0)
		return (handle_append_redirection(data, i));
	else if (ft_strcmp(token, "<<") == 0)
		return (handle_heredoc_redirection(data, i));
	return (0);
}

int	handle_multi_redirections(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd[i])
	{
		if (is_redirection_token(data->cmd[i]))
		{
			if (execute_redirection(data, &i, data->cmd[i]) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (1);
}
