/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quoted_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:00:00 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/05/18 10:00:00 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*resize_buffer(t_parser *parser)
{
	size_t	old_cap;
	char	*new_buf;

	old_cap = parser->cap;
	parser->cap *= 2;
	new_buf = ft_realloc(parser->buf, old_cap, parser->cap);
	return (new_buf);
}

static void	handle_normal_char(const char **p, t_parser *parser)
{
	char	*new_buf;

	if (parser->len + 1 >= parser->cap)
	{
		new_buf = resize_buffer(parser);
		if (!new_buf)
			return ;
		parser->buf = new_buf;
	}
	parser->buf[parser->len++] = *(*p)++;
}

static void	handle_quoted_content(const char **p, char quote, t_parser *parser)
{
	char	*new_buf;

	while (**p && **p != quote)
	{
		if (parser->len + 1 >= parser->cap)
		{
			new_buf = resize_buffer(parser);
			if (!new_buf)
				return ;
			parser->buf = new_buf;
		}
		parser->buf[parser->len++] = *(*p)++;
	}
	if (**p == quote)
		(*p)++;
}

static char	*read_word(const char **p)
{
	t_parser	parser;
	char		quote;

	parser.cap = 64;
	parser.len = 0;
	parser.buf = malloc(parser.cap);
	if (!parser.buf)
		return (NULL);
	while (**p && !ft_isspace((unsigned char)**p))
	{
		if (**p == '\\' && *(*p + 1))
		{
			(*p)++;
			handle_normal_char(p, &parser);
		}
		else if (**p == '"' || **p == '\'')
		{
			quote = *(*p)++;
			handle_quoted_content(p, quote, &parser);
		}
		else
			handle_normal_char(p, &parser);
	}
	parser.buf[parser.len] = '\0';
	return (parser.buf);
}

char	**ft_split_quoted(const char *s)
{
	size_t		wc;
	size_t		i;
	char		**res;
	const char	*p;

	wc = ft_count_words_quoted(s);
	i = 0;
	p = s;
	res = malloc((wc + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < wc)
	{
		while (*p && ft_isspace((unsigned char)*p))
			p++;
		res[i++] = read_word(&p);
		while (*p && ft_isspace((unsigned char)*p))
			p++;
	}
	res[i] = NULL;
	return (res);
}
