/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:47:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/01 01:24:17 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char	*next_word_start(char *s)
{
	while (*s && (*s == ' ' || *s == '\t' || *s == '\n'))
		s++;
	return (s);
}

char	*next_word_end(char *s, char qot_c)
{
	if (qot_c)
	{
		while (*s && *s != qot_c)
			s++;
		if (*s == qot_c)
			return (s);
	}
	else
		while (*s && *s != ' ' && *s != '\t' && *s != '\'' && *s != '"')
			s++;
	return (s);
}

static int	is_valid_quote(char *s)
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

static unsigned int	count_words_buff(char *str)
{
	int		i;
	char	qot_c;

	i = 0;
	while (*str)
	{
		str = next_word_start(str);
		if (*str == '\'' || *str == '"')
			qot_c = *str++;
		else
			qot_c = 0;
		str = next_word_end(str, qot_c);
		if (qot_c && *str == qot_c)
			str++;
		i++;
	}
	return (i);
}

char	**ft_split_buff(t_data *data)
{
	size_t	i;
	size_t	word_count;
	char	**strs;

	i = 0;
	if (!data->buffer || !is_valid_quote(data->buffer))
	{
		ft_putstr_fd("Error! [Open Quotes]\n", 2);
		data->error->status = 2;
		return (NULL);
	}
	word_count = count_words_buff(data->buffer) + 1;
	strs = (char **)malloc(sizeof(char *) * word_count);
	if (!strs)
	{
		ft_putstr_fd("Error! [Malloc Split]\n", 2);
		data->error->status = 12;
		return (NULL);
	}
	ft_process(data, strs, &i);
	strs[i] = NULL;
	return (strs);
}
