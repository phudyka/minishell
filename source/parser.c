/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:52:53 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/17 16:02:11 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int check_bracket(char **argv)
{
    return (0);
}

void    wildcard(char **argv)
{
    
}

void    parser(char **argv)
{   
    if (!check_bracket(argv))
        parsing_error();
    wildcard(argv);
}