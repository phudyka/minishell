/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:38:52 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/17 09:37:11 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// -- ERROR CODE -- //
# define	OK		0 // [OK]
# define	A_KO	3 // [Argument error] 
# define	P_KO	4 // [Parser error]
# define	L_KO	5 // [Lexer error]
# define	X_KO	6 // [Exec error]
# define	E_KO	7 // [Exit error]

int     shell_ok(void);
int     parser(int argc, char **argv);
int     parsing_error(int code);
int     fatal_error(int code, int fd);
long    ft_atoi(char *str);
void    ft_putstr_fd(char *s, int fd);

#endif