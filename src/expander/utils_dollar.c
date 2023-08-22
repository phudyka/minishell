/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:21:15 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/22 05:01:48 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

char	*handle_mark(t_data *data, const char *str, size_t *i, char *output, size_t *j)
{
	char	*status_str;

	if (str[*i + 1] == '?')
	{
		status_str = ft_itoa(data->status);
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
