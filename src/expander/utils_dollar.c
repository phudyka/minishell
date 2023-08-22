/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:21:15 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/22 14:39:09 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

char	*handle_mark(t_data *data, const char *str, char *output,
						size_t indices[2])
{
	char	*status_str;

	if (str[indices[0] + 1] == '?')
	{
		status_str = ft_itoa(data->error->status);
		if (!status_str)
			return (NULL);
		ft_strcpy(output + indices[1], status_str);
		indices[1] += ft_strlen(status_str);
		indices[0] += 2;
		free(status_str);
		return (output);
	}
	return (NULL);
}
