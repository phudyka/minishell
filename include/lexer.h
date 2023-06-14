/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:09:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/13 16:27:29 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "error.h"
# include "parser.h"
# include "../libft/libft.h"

typedef enum
{
    QOT, // quotes /' /"
    RDR, // input '<' and truncate '>'
    PIP, // pipe '|'
    CMD, // commande
    STR, // string
}           token;

typedef struct	s_token
{
	token			type;
	char			*value;
	struct s_token	*next;
}				t_token;


void	parse_pipes(t_token *tokens);
void	parse_quotes(t_token *tokens);
void    master_parser(t_token *token);
char    **master_lexer(char *buff);

#endif