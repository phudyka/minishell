/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:22:34 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/03 15:27:45 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

static void	redir_in(t_token *tokens)
{
	int	fd;
	
	// if (!tokens->next || tokens->next->type != STR)
	// 	ft_error(RDR, 1);
	fd = open(tokens->next->value, O_RDONLY);
	if (fd < 0)
		ft_error(RDR, 2);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error(RDR, 3);
	close(fd);
}

static void	redir_out(int app, t_token *tokens)
{
	int	fd;
	
	if (app)
		fd = open(tokens->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(tokens->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_error(RDR, 2);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_error(RDR, 3);
	close(fd);
}

static void	redir_hdc(t_token *tokens)
{
	int		fd[2];
	char	*max;
	char	*line;
	
	pipe(fd);
	max = tokens->next->value;
	while (1)
	{
		line = readline("heredoc>");
		if (ft_strcmp(line, max) == 1)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	if (dup2(fd[0], STDOUT_FILENO) == -1)
		ft_error(RDR, 3);
	close(fd[0]);
}

void	parse_redir(t_token *tokens)
{
	while (tokens)
	{
		if ((tokens->type == STR || tokens->type == QOT)
			&& tokens->next->type == RDR)
		{
			if (tokens->next->next->type != STR)
				ft_error(RDR, 1);
			if (ft_strcmp(tokens->next->value, "<") == 0)
				redir_in(tokens->next);
			else if (ft_strcmp(tokens->next->value, ">") == 0)
				redir_out(0, tokens->next);
			else if (ft_strcmp(tokens->next->value, ">>") == 0)
				redir_out(1, tokens->next);
			else if (ft_strcmp(tokens->next->value, "<<") == 0)			
				redir_hdc(tokens->next);				
			else
				ft_error(RDR, 2);
		}
		tokens = tokens->next;
	}
}