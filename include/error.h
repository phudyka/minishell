/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:24:09 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/13 16:55:18 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define FATAL	99

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "main.h"
# include "lexer.h"

void	fatal_error(t_data *data, t_env *env, t_token *tokens);
void	ft_error(int token, int code, t_data *data, t_env *env, t_token *tokens);

#endif
