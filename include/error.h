/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:24:09 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/14 14:39:07 phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MALLOC 42
# define FATAL	99

# include "main.h"

typedef struct s_shell t_shell;

void	fatal_error(int code, t_shell *shell);
void	ft_error(int code, int token, t_shell *shell);

#endif
