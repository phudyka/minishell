/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:35:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/16 03:09:21 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "main.h"
# include "error.h"
# include "expander.h"
# include "../libft/libft.h"

int				is_char(char c);
int				is_meta(char c);
int				is_space(char c);
int				is_squote(char c);
int				is_dquote(char c);
void			free_array(char **tab);
void			ft_process(t_data *data, char **strs, size_t *i);
char		*next_word_start(char *s);
char		*next_word_end(char *s, char qot_c);

#endif
