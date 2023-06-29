/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:22:34 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/28 12:21:05 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	redir_in(t_token *tokens)
{
	int	fd;
	
	if (!tokens->next || tokens->next->type != STR)
		ft_error(RDR, 1);
	fd = open(tokens->next->value, O_RDONLY);
	if (fd == -1)
		ft_error(RDR, 2);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	redir_out(t_token *tokens)
{
	int	fd;
	
	if (!tokens->next || tokens->next->type != STR)
		ft_error(RDR, 1);
	fd = open(tokens->next->value, O_WRONLY, O_CREAT, O_TRUNC, 0644);
	if (fd == -1)
		ft_error(RDR, 2);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	redir_app(t_token *tokens)
{
	int	fd;
	
	if (!tokens->next || tokens->next->type != STR)
		ft_error(RDR, 1);
	fd = open(tokens->next->value, O_WRONLY, O_CREAT, O_APPEND, 0644);
	if (fd == -1)
		ft_error(RDR, 2);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	redir_hdc(t_token *tokens)
{
	int		fd[2];
	char	*max;
	char	*line;
	
	if (!tokens->next || tokens->next->type != STR)
		ft_error(RDR, 1);
	pipe(fd);
	max = tokens->next->value;
	while (1)
	{
		line = readline(tokens->value);
		if (ft_strcmp(line, max) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], STDOUT_FILENO);
	close(fd[0]);
}

void	parse_redir(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == RDR)
		{
			if (ft_strcmp(tokens->value, "<") == 0)
				redir_in(tokens);
			else if (ft_strcmp(tokens->value, ">") == 0)
				redir_out(tokens);
			else if (ft_strcmp(tokens->value, "<<") == 0)			
				redir_app(tokens);
			else if (ft_strcmp(tokens->value, ">>") == 0)
				redir_hdc(tokens);				
			else
				ft_error(RDR, 0);
		}
		tokens = tokens->next;
	}
}