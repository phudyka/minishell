/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:24:09 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/09 11:57:27 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define FATAL	99 // Fatal error causing minishell to stop

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	fatal_error(int code);
void	ft_error(int case, int code);

#endif