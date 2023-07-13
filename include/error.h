/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:24:09 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/13 10:01:20 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MALLOC	42
# define FATAL	99

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "lexer.h"

void	fatal_error(int code);
void	ft_error(int token, int code);

#endif
