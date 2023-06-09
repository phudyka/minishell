/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:35:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/09 10:30:36 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include "lexer.h"
#include "error.h"
# include "../libft/libft.h"

int     is_char(char c);
int     is_space(char c);
int     is_quote(char c);
int     metachar(char c);
void    free_array(char **tab);
void	parse_pipes(t_token *tokens);
void	parse_quotes(t_token *tokens);

#endif