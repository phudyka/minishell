/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:42:55 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/10 10:10:52 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/error.h"

static void	redir_error(int code)
{
	if (code == 1)
		perror("Error! [parse error near `\n']\n");
	if (code == 2)
		perror("Error! [open failed]\n");
	if (code == 3)
	{
		ft_putstr_fd("Error! [dup2 failed]\n", 2);
		g_shell.status = 37;
	}
	return ;
}

static void	quote_error(int code)
{
	if (code)
	{
		ft_putstr_fd("Error! [quotes open]\n", 2);
		g_shell.status = 2;
	}
	return ;
}

static void	pipe_error(int code)
{
	if (code)
	{
		ft_putstr_fd("Error! [pipe]\n", 2);
		g_shell.status = 32;
	}
	return ;
}

void	ft_error(int token, int code)
{
	if (token == PIP)
		pipe_error(code);
	else if (token == RDR)
		redir_error(code);
	else if (token == QOT)
		quote_error(code);
	else
	{
		ft_putstr_fd("Error! [An unexpected behavior has occured]\n", 2);
		g_shell.status = 1;
	}
}
