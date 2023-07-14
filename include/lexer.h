/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:09:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/14 15:26:19 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "main.h"
typedef enum id
{
	QOT,
	RDR,
	PIP,
	STR,
}			t_id;

typedef struct s_shell t_shell;

void	parse_redir(t_shell *tokens);
void	parse_quotes(t_shell *tokens);
void	master_parser(t_shell *tokens);
void	free_tokens(t_shell *tokens);
char	**master_lexer(char *buff, t_shell *shell);

#endif
