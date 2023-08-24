/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:22:34 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/23 14:16:22 by phudyka          ###   ########.fr       */
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

	if (append)
		fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Error ![open]\n", 2);
		data->error->status = 2;
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("Error! [dup2]\n", 2);
		data->error->status = 35;
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
