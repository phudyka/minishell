/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:32:21 by kali              #+#    #+#             */
/*   Updated: 2023/08/09 22:29:35 by phudyka          ###   ########.fr       */
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
		exit_error("open");
	len = 0;
	line = NULL;
	read = getline(&line, &len, stdin);
	while (read != -1)
	{
		heredoc_line(line, read, fd, delimiter);
		read = getline(&line, &len, stdin);
	}
	close(fd);
	free(line);
}

void	heredoc_line(char *line, ssize_t read, int fd, char *delimiter)
{
	if (read > 0 && line[read - 1] == '\n')
	{
		line[read - 1] = '\0';
		read--;
	}
	if (ft_strcmp(line, delimiter) == 0)
		return ;
	line[read] = '\n';
	write(fd, line, read + 1);
}

void	set_tmp_file_as_stdin(void)
{
	int	fd;

	fd = open("/tmp/minishell_heredoc", O_RDONLY);
	if (fd < 0)
		exit_error("open");
	if (dup2(fd, STDIN_FILENO) < 0)
		exit_error("dup2");
	close(fd);
}

void	check_and_apply_redirection(char **cmd, int *i)
{
	if (ft_strcmp(cmd[*i], "<") == 0)
	{
		redirect_input(cmd, *i);
		remove_redirection(cmd, *i);
	}
	else if (ft_strcmp(cmd[*i], ">") == 0)
	{
		redirect_output(cmd, *i, 0);
		remove_redirection(cmd, *i);
	}
	else if (ft_strcmp(cmd[*i], ">>") == 0)
	{
		redirect_output(cmd, *i, 1);
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
