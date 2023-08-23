/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:21:15 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/23 12:04:10 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

bool	handle_mark(t_data *data, const char *str,
						char *output, size_t *indices)
{
	char	*status_str;

	if (str[indices[0] + 1] == '?')
	{
		status_str = ft_itoa(data->error->status);
		if (!status_str)
			return (false);
		ft_strcpy(output + indices[1], status_str);
		indices[1] += ft_strlen(status_str);
		indices[0] += 2;
		free(status_str);
		return (true);
	}
	return (false);
}
