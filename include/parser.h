/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:35:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/03 16:39:21 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "error.h"
# include "lexer.h"
# include "../libft/libft.h"

int     is_char(char c);
int     is_space(char c);
int     is_quote(char c);
int     metachar(char c);
int		is_squote(char c);
int		is_dquote(char c);
void	ft_dollar(size_t i, size_t j, char  *parsed, const char *value);
void    free_array(char **tab);
char	**split_args(char *buff);

#endif