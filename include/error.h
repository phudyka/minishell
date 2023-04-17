/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:36:22 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/17 11:38:09 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// -- ERROR CODE -- //
# define	OK		0 // [OK]
# define	A_KO	3 // [Argument error] 
# define	P_KO	4 // [Parser error]
# define	L_KO	5 // [Lexer error]
# define	X_KO	6 // [Exec error]
# define	E_KO	7 // [Exit error]

# include <unistd.h>
# include <stdlib.h>

int     fatal_error(int code, int fd);
int     fatal_error(int code, int fd);
void    ft_putstr_fd(char *s, int fd);
void    ft_free();

#endif