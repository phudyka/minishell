/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:23:31 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/21 15:42:52 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

char    **ft_parse(char *buff)
{
    char **cmd;

    cmd = ft_split(buff, ' ');
    if (!ft_quote(*cmd)) // !*cmd
        return(NULL);
    return(cmd);
}