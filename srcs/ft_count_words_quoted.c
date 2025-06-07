/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words_quoted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:00:00 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/05/18 12:00:00 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_cnt_words_init(t_cnt_words *cnt_words)
{
	cnt_words->cnt = 0;
	cnt_words->in_w = 0;
	cnt_words->q = 0;
}

static void	ft_cnt_words_check(t_cnt_words *cnt_words, const char *s)
{
	if (!ft_isspace((unsigned char)*s) && !cnt_words->in_w)
	{
		cnt_words->in_w = 1;
		cnt_words->cnt++;
	}
}

size_t	ft_count_words_quoted(const char *s)
{
	t_cnt_words	cnt_words;

	ft_cnt_words_init(&cnt_words);
	while (*s)
	{
		ft_cnt_words_check(&cnt_words, s);
		if (cnt_words.in_w)
		{
			if (*s == '\\' && s[1])
				s += 2;
			else if (*s == '"' || *s == '\'')
			{
				cnt_words.q = *s++;
				while (*s && *s != cnt_words.q)
					s++;
			}
			else if (ft_isspace((unsigned char)*s))
				cnt_words.in_w = 0;
			if (*s)
				s++;
		}
		else
			s++;
	}
	return (cnt_words.cnt);
}
