/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:22:34 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/01 01:23:24 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

int	redirect_input(t_data *data, char **cmd, int i)
{
	int	fd;

	fd = open(cmd[i + 1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error! [open]\n", 2);
		data->error->status = 2;
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("Error! [dup2]\n", 2);
		data->error->status = 35;
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (fd);
}

int	redirect_output(t_data *data, char **cmd, int i, int append)
{
	int	fd;

	if (!cmd[i + 1])
	{
		data->error->status = 2;
		return (0);
	}
	if (append)
		fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Error ![open]\n", 2);
		data->error->status = 2;
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("Error! [dup2]\n", 2);
		data->error->status = 35;
		return (0);
	}
	close(fd);
	return (fd);
}

void	remove_redirection(char **cmd, int start)
{
	int	i;
	int	len;

	if (cmd[start])
	{
		free(cmd[start]);
		cmd[start] = NULL;
	}
	if (cmd[start + 1])
	{
		free(cmd[start + 1]);
		cmd[start + 1] = NULL;
	}
	len = 0;
	while (cmd[len])
		len++;
	if (start + 2 >= len)
		return ;
	i = start;
	while (cmd[i + 2])
	{
		cmd[i] = cmd[i + 2];
		i++;
	}
	cmd[i] = NULL;
}

void	redirect_here_doc(char **cmd, int i)
{
	char	*delimiter;

	delimiter = cmd[i + 1];
	create_tmp_file(delimiter);
	set_tmp_file_as_stdin();
}

void	redirections(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	if (is_exit_command(cmd[i]))
	{
		data->error->exit = TRUE;
		return ;
	}
	while (cmd[i])
		check_and_apply_redirection(data, cmd, &i);
}
