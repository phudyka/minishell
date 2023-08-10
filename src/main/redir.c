/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:22:34 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/10 10:19:05 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

int	redirect_input(char **cmd, int i)
{
	int	fd;

	fd = open(cmd[i + 1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("open", 2);
		g_shell.status = 2;
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("dup2", 2);
		g_shell.status = 35;
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (fd);
}

int	redirect_output(char **cmd, int i, int append)
{
	int	fd;

	if (append)
		fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("open", 2);
		g_shell.status = 2;
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("dup2", 2);
		g_shell.status = 35;
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (fd);
}

void	remove_redirection(char **cmd, int start)
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

void	redirect_here_doc(char **cmd, int i)
{
	char	*delimiter;

	delimiter = cmd[i + 1];
	create_tmp_file(delimiter);
	set_tmp_file_as_stdin();
}

void	redirections(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		check_and_apply_redirection(cmd, &i);
}
