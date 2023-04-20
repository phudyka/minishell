/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:57:14 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/20 16:18:42 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

char    **ft_parse(char **args)
{
    char    **parsed;

    (void)args;
    parsed = (char**)malloc(sizeof(char *) * 1);
    return(parsed);
}