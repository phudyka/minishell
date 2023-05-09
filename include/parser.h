/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:35:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/09 15:13:18 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
typedef enum token
{
    NUN, // none ""
    IPT, // input '<'
    TRC, // truncate '>'
    PIP, // pipe '|'
    END, // end ';'
    CMD, // commande
    STR, //string       
}           token;

int     is_char(char c);
int     is_space(char c);
int     is_quote(char c);
int     metachar(char c);
char    *ft_chardup(char c);
int     ft_quotes(char *cmd);
void    free_array(char **tab);
char	*parse_arg(char **str);
char	*parse_pipes(char **str);
char	*parse_quotes(char **str);
char    **master_parser(char *buff);
int     skip_quotes(char **str, char quote);

#endif