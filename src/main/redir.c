/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:22:34 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/02 16:06:55 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

static void	redir_in(t_token *tokens)
{
	int	fd;
	
	if (!tokens->next || tokens->next->type != STR)
		ft_error(RDR, 1);
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
	
	if (!tokens->next || tokens->next->type != STR)
		ft_error(RDR, 1);
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
	if (dup2(fd[0], STDOUT_FILENO) == -1)
		ft_error(RDR, 3);
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
				redir_out(0, tokens);
			else if (ft_strcmp(tokens->value, ">>") == 0)
				redir_out(1, tokens);
			else if (ft_strcmp(tokens->value, "<<") == 0)			
				redir_hdc(tokens);				
			else
				ft_error(RDR, 2);
		}
		tokens = tokens->next;
	}
}