/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:09:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/06 16:31:17 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef enum
{
    NUN, // none ""
    IPT, // input '<'
    TRC, // truncate '>'
    PIP, // pipe '|'
	HDC, // heredoc '<<'
	APP, // append '>>'
    CMD, // commande
    STR, // string
    LPR, // left parenthesis       
    RPR  // right parenthesis       
}           token;

typedef struct	s_token
{
	token			type;
	char			*value;
	struct s_token	*next;
}				t_token;

char    *ft_chardup(char c);
char    **master_lexer(char *buff);
void    master_parser(t_token *token);

#endif