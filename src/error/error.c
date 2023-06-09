/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:42:55 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/09 11:57:12 by phudyka          ###   ########.fr       */
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

void	ft_error(int case, int code)
{
	if (case = CMD)
		cmd_error(code);
	else if (case == PIP)
		pipe_error(code);
	else if (case = RDR)
		redir_error(code);
	else if (case = QOT)
		quote_error(code);
	else if (case == FATAL)
		fatal_error(code);
	else
		ft_putstr_fd("Error! [An unexpected behavior has occured]\n", 2);
}