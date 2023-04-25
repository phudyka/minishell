/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:12:56 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/25 16:22:28 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int ft_token(char *str)
{
    if (is_command(str))
        return(CMD);
    else if (is_string(str))
        return(STR);
    else if (is_)
}