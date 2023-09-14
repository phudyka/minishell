/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:32:21 by kali              #+#    #+#             */
/*   Updated: 2023/09/14 08:13:09 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	is_redirection_token(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, ">") == 0 || ft_strcmp(cmd, ">>") == 0
		|| ft_strcmp(cmd, "<") == 0 || ft_strcmp(cmd, "<<") == 0);
}

int	is_next_token_invalid(t_data *data, int i)
{
	if (!data->cmd[i + 1] || is_redirection_token(data->cmd[i + 1]))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		data->error->status = 2;
		return (1);
	}
	return (0);
}

int	handle_output_redirection(t_data *data, int *i)
{
	int	fd;

	if (is_next_token_invalid(data, *i))
		return (-1);
	fd = open(data->cmd[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->cmd[*i + 1], 2);
		ft_putstr_fd(": Permission denied\n", 2);
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

int	handle_input_redirection(t_data *data, int *i)
{
	int	fd;

	if (is_next_token_invalid(data, *i))
		return (-1);
	fd = open(data->cmd[*i + 1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->cmd[*i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->error->status = 1;
		free_data(data);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(data->cmd[*i]);
	free(data->cmd[*i + 1]);
	data->cmd[*i] = NULL;
	data->cmd[*i + 1] = NULL;
	(*i) += 2;
	return (1);
}
