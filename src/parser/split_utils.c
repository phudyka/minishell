/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:25:33 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/16 11:31:27 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	**sub_start_to_end(t_data *data, char *start, const char *end,
		char **strs, size_t *i)
{
	char	*sub;

	if (*start == '\'' || *start == '"')
	{
		start++;
		end--;
	}
	sub = ft_substr(start, 0, end - start);
	if (!sub)
	{
		while (*i > 0)
			free(strs[--(*i)]);
		free(strs);
		return (NULL);
	}
	if (*start == '\'')
		strs[(*i)++] = sub;
	else
	{
		strs[(*i)++] = ft_dollar(data, sub, false);
		free(sub);
	}
	return (strs);
}

static void	process_without_quote(t_data *data, char **s, char **strs, size_t *i)
{
	char	*start;
	char	*end;

	start = *s;
	*s = next_word_end(*s, 0);
	end = *s;
	if (start < end)
		sub_start_to_end(data, start, end, strs, i);
}

static void	process_single_quote(t_data *data, char *start, char **strs, size_t *i)
{
	const char	*end;

	(void)data;
	end = next_word_end(start, '\'') - 1;
	strs[(*i)++] = ft_substr(start, 0, end - start);
}

static void	process_double_quote(t_data *data, char *start, char **strs, size_t *i)
{
	const char	*end;
	char		*intermediate_sub;

	end = next_word_end(start, '"') - 1;
	intermediate_sub = ft_substr(start, 0, end - start);
	if (strchr(intermediate_sub, '$'))
	{
		strs[(*i)++] = ft_dollar(data, intermediate_sub, 0);
		free(intermediate_sub);
	}
	else
		strs[(*i)++] = intermediate_sub;
}

void	ft_process(t_data *data, char **strs, size_t *i)
{
	char	qot;
    char    *buffer_copy;

    buffer_copy = data->buffer;
	while (*buffer_copy)
	{
		buffer_copy = next_word_start(buffer_copy);
		if (*buffer_copy == '\'' || *buffer_copy == '"')
		{
			qot = *buffer_copy++;
			if (qot == '\'')
				process_single_quote(data, buffer_copy, strs, i);
			else
				process_double_quote(data, buffer_copy, strs, i);
			buffer_copy = next_word_end(buffer_copy, qot);
		}
		else
			process_without_quote(data, &buffer_copy, strs, i);
	}
}
