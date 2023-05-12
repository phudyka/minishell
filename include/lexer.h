/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:09:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/12 10:10:05 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "parser.h"

typedef enum token
{
    NUN, // none ""
    IPT, // input '<'
    TRC, // truncate '>'
    PIP, // pipe '|'
    END, // end ';'
	HDC, // heredoc '<<'
	APP, // append '>>'
    CMD, // commande
    STR, //string       
}           token;

typedef struct	s_token
{
	token			type;
	char			*value;
	struct s_token	*next;
}				t_token;

char **master_lexer(char *buff);

#endif