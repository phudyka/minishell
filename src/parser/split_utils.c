/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:25:33 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/22 14:31:53 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../../include/parser.h"

static char	**sub_start_to_end(char *start, const char *end,
	char **strs, size_t *i)
{
	char	*sub;

	sub = ft_substr(start, 0, end - start);
	if (!sub)
	{
		while (*i > 0)
			free(strs[--(*i)]);
		free(strs);
		return (NULL);
	}
	strs[(*i)++] = sub;
	return (strs);
}

static void	no_quote(t_data *data, char **s,
	char **strs, size_t *i)
{
	char	*start;
	char	*end;
	char	*expanded;

	start = *s;
	end = next_word_end(*s, 0);
	if (start[0] == '$')
	{
		expanded = ft_dollar(data, start, 0);
		if (expanded)
		{
			strs[(*i)++] = expanded;
			*s += ft_strlen(start);
		}
	}
	else if (start < end)
		sub_start_to_end(start, end, strs, i);
	*s = end;
}

static void	s_quote(char **s, char **strs, size_t *i)
{
	char	*start;
	char	*end;

	start = *s;
	end = next_word_end(start + 1, '\'');
	sub_start_to_end(start, end, strs, i);
	*s = end;
}

static void	d_quote(t_data *data, char **s, char **strs, size_t *i)
{
	char	*start;
	char	*end;
	char	*sub;
	char	*expanded;

	start = *s;
	end = next_word_end(start + 1, '"');
	sub = ft_substr(start, 0, end - start);
	if (ft_strchr(sub, '$'))
	{
		expanded = ft_dollar(data, sub, 0);
		free(sub);
		strs[(*i)++] = expanded;
	}
	else
		strs[(*i)++] = sub;
	*s = end;
}

void	ft_process(t_data *data, char **strs, size_t *i)
{
	char	*s;

	s = data->buffer;
	while (*s)
	{
		s = next_word_start(s);
		if (*s == '\'')
			s_quote(&s, strs, i);
		else if (*s == '"')
			d_quote(data, &s, strs, i);
		else
			no_quote(data, &s, strs, i);
	}
}
