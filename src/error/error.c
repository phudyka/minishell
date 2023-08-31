/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:22:27 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/31 11:50:49 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	redir_error(t_error *error, int code)
{
	if (code == 1)
	{
		perror("Error! [parse error near `newline']\n");
		error->status = 2;
	}
	if (code == 2)
	{
		perror("Error! [open failed]\n");
		error->status = 1;
	}
	if (code == 3)
	{
		ft_putstr_fd("Error! [dup2 failed]\n", 2);
		error->status = 37;
	}
	return ;
}

static void	quote_error(t_error *error, int code)
{
	if (code)
	{
		ft_putstr_fd("Error! [quotes open]\n", 2);
		error->status = 2;
	}
	return ;
}

static void	pipe_error(t_error *error, int code)
{
	if (code)
	{
		ft_putstr_fd("Error! [pipe]\n", 2);
		error->status = 32;
	}
	return ;
}

void	ft_error(t_error *error, int token, int code)
{
	if (token == PIP)
		pipe_error(error, code);
	else if (token == RDR)
		redir_error(error, code);
	else if (token == QOT)
		quote_error(error, code);
	else if (token == MLC)
	{
		ft_putstr_fd("Error! [Malloc]\n", 2);
		error->status = 12;
	}
	else
	{
		ft_putstr_fd("Error! [An unexpected behavior has occured]\n", 2);
		error->status = 1;
	}
}

void	init_error(t_error *error)
{
	error->status = 0;
	error->exit = FALSE;
}
