/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:32:21 by kali              #+#    #+#             */
/*   Updated: 2023/09/01 01:05:49 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	create_tmp_file(char *delimiter)
{
	char	*line;
	size_t	len;
	ssize_t	read;
	int		fd;

	fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		exit_error("Error [open]\n");
	len = 0;
	line = NULL;
	read = getline(&line, &len, stdin);
	while (read != -1)
	{
		if (heredoc_line(line, read, fd, delimiter))
			break ;
		read = getline(&line, &len, stdin);
	}
	close(fd);
	free(line);
}

int	heredoc_line(char *line, ssize_t read, int fd, char *delimiter)
{
	if (read > 0 && line[read - 1] == '\n')
	{
		line[read - 1] = '\0';
		read--;
	}
	if (ft_strcmp(line, delimiter) == 0)
		return (1);
	line[read] = '\n';
	write(fd, line, read + 1);
	return (0);
}

void	set_tmp_file_as_stdin(void)
{
	int	fd;

	fd = open("/tmp/minishell_heredoc", O_RDONLY);
	if (fd < 0)
		exit_error("Error! [open]\n");
	if (dup2(fd, STDIN_FILENO) < 0)
		exit_error("Error[dup2]\n");
	close(fd);
}

void	check_and_apply_redirection(t_data *data, char **cmd, int *i)
{
	if (ft_strcmp(cmd[*i], "<") == 0)
	{
		redirect_input(data, cmd, *i);
		remove_redirection(cmd, *i);
	}
	else if (ft_strcmp(cmd[*i], ">") == 0)
	{
		redirect_output(data, cmd, *i, 0);
		remove_redirection(cmd, *i);
	}
	else if (ft_strcmp(cmd[*i], ">>") == 0)
	{
		redirect_output(data, cmd, *i, 1);
		remove_redirection(cmd, *i);
	}
	else if (ft_strcmp(cmd[*i], "<<") == 0)
	{
		redirect_here_doc(cmd, *i);
		remove_redirection(cmd, *i);
	}
	else
		(*i)++;
}
