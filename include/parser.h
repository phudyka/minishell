/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:35:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/09 11:18:33 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

/*enum    s_token
{
    CMD,
    STR,       
}       t_token;*/

int     is_char(char c);
int     is_quote(char c);
int     metachar(char c);
int     ft_quotes(char *cmd);
char    *ft_chardup(char c);
void    free_array(char **tab);
char	*parse_quotes(char **str);
char	*parse_pipes(char **str);
char	*parse_arg(char **str);
char    **master_parser(char *buff);

#endif