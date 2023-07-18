/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:24:09 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/18 11:56:03 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MALLOC	42
# define FATAL	99

# include "main.h"

void	fatal_error(int code);
void	ft_error(int token, int code);

#endif
