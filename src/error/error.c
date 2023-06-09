/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:42:55 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/09 15:05:41 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/error.h"

static void	redir_error(int code)
{
	if (code)
		ft_putstr_fd("Error! [redirection]\n", 2);
}

static void	quote_error(int code)
{
	if (code)
		ft_putstr_fd("Error! [quote]\n", 2);
}

static void	pipe_error(int code)
{
	if (code)
		ft_putstr_fd("Error! [pipe]\n", 2);
}

static void	cmd_error(int code)
{
	if (code)
		ft_putstr_fd("Error! [command]\n", 2);
}

void	ft_error(int token, int code)
{
	if (token == CMD)
		cmd_error(code);
	else if (token == PIP)
		pipe_error(code);
	else if (token == RDR)
		redir_error(code);
	else if (token == QOT)
		quote_error(code);
	else if (token == FATAL)
		fatal_error(code);
	else
		ft_putstr_fd("Error! [An unexpected behavior has occured]\n", 2);
}