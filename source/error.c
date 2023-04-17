/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:42:49 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/17 14:56:40 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/error.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
}

int parsing_error(int code)
{
    if (code == A_KO)
        printf("Error! : [Bad Arguments]\n");
    else if (code == P_KO)
        printf("Error! : [Parsing Failure]\n");
    else if (code == L_KO)
        printf("Error! : [Lexer Failure]\n");
    else if (code == X_KO)
        printf("Error! : [Command Exec. Failure]\n");
    else if (code == E_KO)
        printf("Error! : [Exit Failure]\n");
}

int fatal_error(int code, int fd)
{
    return(1);
}

void    ft_free()
{
    
}