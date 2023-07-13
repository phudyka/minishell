/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:57:01 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/13 13:58:22 by phudyka          ###   ########.fr       */
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
# include "error.h"
# include "lexer.h"
# include "expander.h"
# include "../libft/libft.h"

int		is_char(char c);
int		is_meta(char c);
int		is_space(char c);
int		is_squote(char c);
int		is_dquote(char c);
void	free_array(char **tab);

#endif
