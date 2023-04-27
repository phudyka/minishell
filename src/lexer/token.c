/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:12:56 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/27 10:59:30 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int ft_token(char *str)
{
    if (is_builtin(str))
        return(CMD);
    else if (is_string(str))
        return(STR);
    else if (is_)
}