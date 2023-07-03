/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:58:28 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/03 16:48:24 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	is_squote(char c)
{
	return (c == '\'');
}

int	is_dquote(char c)
{
	return (c == '\"');
}

int is_space(char c)
{
    return(c == ' ');
}

/*void ft_dollar(size_t i, size_t j,
        char *parsed, const char *value)
{
 
}*/