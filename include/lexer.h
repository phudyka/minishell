/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:09:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/13 16:38:27 by phudyka          ###   ########.fr       */
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

typedef enum id
{
	QOT,
	RDR,
	PIP,
	STR,
}			t_id;

typedef struct s_token
{
	t_id			type;
	char			*value;
	struct s_token	*next;
}			t_token;

void	parse_redir(t_token *tokens);
void	parse_quotes(t_token *tokens);
void	master_parser(t_token *tokens);
void	free_tokens(t_token *tokens);
char	**master_lexer(char *buff, t_token *tokens);

#endif
