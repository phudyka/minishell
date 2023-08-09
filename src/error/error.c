/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:42:55 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/09 17:24:44 by phudyka          ###   ########.fr       */
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
		perror("Error! [dup2 failed]\n");
	return ;
}

static void	quote_error(int code)
{
	if (code)
		perror("Error! [quotes open]\n");
	return ;
}

static void	pipe_error(int code)
{
	if (code)
		perror("Error! [pipe]\n");
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
		perror("Error! [An unexpected behavior has occured]\n");
}
