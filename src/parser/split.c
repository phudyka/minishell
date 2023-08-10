/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:47:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/10 15:00:04 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

const char	*next_word_start(const char *s)
{
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return (s);
}

const char	*next_word_end(const char *s, char qot_c)
{
	if (qot_c)
	{
		while (*s && *s != qot_c)
			s++;
		if (*s == qot_c)
			s++;
	}
	else
	{
		while (*s && *s != ' ' && *s != '\t' && *s != '\'' && *s != '"')
			s++;
	}
	return (s);
}

static int	is_valid_quote(const char *s)
{
	char	qot_c;

	qot_c = 0;
	while (*s)
	{
		if (qot_c == 0 && (*s == '\'' || *s == '"'))
			qot_c = *s;
		else if (*s == qot_c)
			qot_c = 0;
		s++;
	}
	return (qot_c == 0);
}

static unsigned int	count_words_buff(const char *str)
{
	int		i;
	char	qot_c;

	i = 0;
	while (*str)
	{
		str = next_word_start(str);
		if (*str == '\'' || *str == '"')
			qot_c = *str;
		else
			qot_c = 0;
		if (qot_c)
			str++;
		str = next_word_end(str, qot_c);
		if (qot_c && *str == qot_c)
			str++;
		i++;
	}
	return (i);
}

char	**ft_split_buff(const char *s)
{
	size_t	i;
	char	**strs;

	i = 0;
	if (!s || !is_valid_quote(s))
	{
		perror("Error! : [Open Quotes]\n");
		return (NULL);
	}
	strs = (char **)malloc(sizeof(char *) * (count_words_buff(s) + 1));
	if (!strs)
	{
		perror("Error! [Malloc Split]\n");
		return (NULL);
	}
	ft_process(s, strs, &i);
	strs[i] = NULL;
	return (strs);
}
