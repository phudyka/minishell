/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:22:34 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/09 17:16:28 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

int redirect_input(char **cmd, int i)
{
	int fd;

	fd = open(cmd[i + 1], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (fd);
}

int redirect_output(char **cmd, int i, int append)
{
	int	fd;

	if (append)
		fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
	return fd;
}

void remove_redirection(char **cmd, int start)
{
    free(cmd[start]);
    free(cmd[start + 1]);
    if (!cmd[start + 2])
        cmd[start] = NULL;
    else
    {
        while (cmd[start + 2])
        {
            cmd[start] = cmd[start + 2];
            start++;
        }
        cmd[start] = NULL;
    }
}

void redirect_here_doc(char **cmd, int i)
{
    char	*delimiter;
    char	*line;
    size_t	len;
    ssize_t	read;
    int		fd;

	fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	len = 0;
	line = NULL;
	delimiter = cmd[i + 1];
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    printf("Enter lines of text, end with '%s'\n", delimiter);
    while ((read = getline(&line, &len, stdin)) != -1) 
    {
        if (read > 0 && line[read - 1] == '\n')
        {
            line[read - 1] = '\0';
            read--;
        }
        printf("Read line: %s\n", line);
        if (ft_strcmp(line, delimiter) == 0)
            break;
        line[read] = '\n';
        write(fd, line, read + 1);
    }
    close(fd);
    free(line);
    fd = open("/tmp/minishell_heredoc", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void redirections(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (ft_strcmp(cmd[i], "<") == 0)
        {
            redirect_input(cmd, i);
            remove_redirection(cmd, i);
        }
        else if (ft_strcmp(cmd[i], ">") == 0)
        {
            redirect_output(cmd, i, 0);
            remove_redirection(cmd, i);
        }
        else if (ft_strcmp(cmd[i], ">>") == 0)
        {
            redirect_output(cmd, i, 1);
            remove_redirection(cmd, i);
        }
        else if (ft_strcmp(cmd[i], "<<") == 0)
        {
            redirect_here_doc(cmd, i);
            remove_redirection(cmd, i);
        }
        else
            i++;
    }
}