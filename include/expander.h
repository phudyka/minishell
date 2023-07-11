/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:16:09 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/11 15:27:02 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "parser.h"

void	master_expander(char meta, const char *str);

#endif