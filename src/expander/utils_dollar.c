/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 07:02:53 by kali              #+#    #+#             */
/*   Updated: 2023/08/10 07:18:16 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

char	*handle_mark(const char *str, size_t *i, char *output, size_t *j)
{
	char	*status_str;

	if (str[*i + 1] == '?')
	{
		status_str = ft_itoa(g_shell.status);
		if (!status_str)
			return (NULL);
		ft_strcpy(output + *j, status_str);
		*j += ft_strlen(status_str);
		*i += 2;
		free(status_str);
		return (output);
	}
	return (NULL);
}
