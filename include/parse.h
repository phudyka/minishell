/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:57:08 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/24 14:45:43 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

int     is_char(char c);
int     is_quote(char c);
int     metachar(char c);
int     ft_quotes(char *cmd);
char    *ft_chardup(char c);
char	*parse_quotes(char **str);
char	*parse_arg(char **str);
char    **master_parser(char *buff);

#endif