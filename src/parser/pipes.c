/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:15:37 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/28 11:45:10 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

char    *parse_pipes(char **str)
{
    char    *cmd1;
    char    *cmd2;
    char    *pipe;

    cmd1 = ft_strtrim(*str, " ");
    cmd2 = NULL;
    pipe = ft_strchr(cmd1, '|');
    if (!pipe)
    {
        if (is_builtin(cmd1))
        {
            free(cmd1);
            cmd1 = NULL;
            return (NULL);
        }
        else
            return (cmd1);
    }
    *pipe++ = '\0';
    cmd2 = ft_strtrim(pipe, " ");
    if (is_builtin(cmd1) || is_builtin(cmd2))
        return (NULL);
    *str = pipe;
    return (cmd1);
}