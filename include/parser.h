/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:35:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/15 18:08:35 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

int     is_char(char c);
int     is_space(char c);
int     is_quote(char c);
int     metachar(char c);
int     ft_quotes(char *cmd);
void    free_array(char **tab);
char	*parse_quotes(char **str);
int     skip_quotes(char **str, char quote);

#endif