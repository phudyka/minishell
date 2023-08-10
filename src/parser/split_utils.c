/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:25:33 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/10 15:13:35 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	**sub_start_to_end(const char *start, const char *end,
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
	strs[(*i)++] = ft_dollar(sub, (*start == '\''));
	free(sub);
	return (strs);
}

static void	process_with_quote(const char **s, char qot, char **strs, size_t *i)
{
	const char	*start;
	const char	*end;

	start = *s;
	*s = next_word_end(*s + 1, qot);
	end = *s;
	if (start < end)
		sub_start_to_end(start, end, strs, i);
}

static void	process_without_quote(const char **s, char **strs, size_t *i)
{
	const char	*start;
	const char	*end;

	start = *s;
	*s = next_word_end(*s, 0);
	end = *s;
	if (start < end)
		sub_start_to_end(start, end, strs, i);
}

void	ft_process(const char *s, char **strs, size_t *i)
{
	char		qot;

	while (*s)
	{
		s = next_word_start(s);
		if (*s == '\'' || *s == '"')
		{
			qot = *s++;
			process_with_quote(&s, qot, strs, i);
		}
		else
			process_without_quote(&s, strs, i);
	}
}
