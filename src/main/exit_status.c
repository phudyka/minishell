/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:22:05 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/11 16:50:42 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/main.h"

int exit_status(char *buffer)
{
    int     i;
    int     code;

    i = 6;
    code = 0;
    printf("buffer = %s\n", buffer);
    if (!buffer)
        return (0);
    while (buffer[i])
    {
        if (ft_isdigit(buffer[i]) && (buffer[i + 1] != ' ' || buffer[i + 1] != '\t'))
            code = ft_atoi(buffer);
        else if (ft_atoi(buffer) < INT_MIN || ft_atoi(buffer) > INT_MIN)
            code = 256;
        else if (ft_isalpha(buffer[i]))
        {
            printf("exit\nbash: exit: %s: numeric argument require", buffer);
            return (2);
        }
        i++;  
    }
    printf("exit\n");
    return (code);
}