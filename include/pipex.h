/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:59:43 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/05/17 00:00:00 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>       /* strerror */
# include "../libft/libft.h"

typedef struct s_cnt_wrods
{
	size_t	cnt;
	int		in_w;
	char	q;
}	t_cnt_words;

typedef struct s_parser
{
	char	*buf;
	size_t	cap;
	size_t	len;
}	t_parser;

typedef struct s_pipex
{
	int		fd[2];
	int		infile;
	int		outfile;
	int		status1;
	int		status2;
	int		status_code;
	int		ac;
	char	**av;
	char	**envp;
	char	**cmd1;
	char	**cmd2;
	char	*r;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

/* main.c */
void	run_pipeline(t_pipex *ctx);

/* child.c */
void	child_process1(t_pipex *ctx);
void	child_process2(t_pipex *ctx);

/* execute.c */
void	execute(t_pipex *ctx, int cmd_num);

/* find_path.c */
char	*search_paths(char **paths, char *cmd);
char	*find_path(t_pipex *ctx, char *cmd);

/* utils.c */
void	ft_free(char **strs);
void	init_pipex(t_pipex *ctx);
void	clean_pipex(t_pipex *ctx);
void	error_exit(char *msg, int exit_code);
char	*ft_getenv(char *envp[], const char *name);
int		is_directory(char *path);
int		ft_isspace(int c);

/* parse_quoted_cmd.c */
char	**ft_split_quoted(const char *s);

/* parser_helpers.c */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
// int		buf_add(char **buf, size_t *cap, size_t *len, char c);
// int		parse_escape(const char **p, char **buf, size_t *cap, size_t *len);
// int		parse_quoted(const char **p, char **buf, size_t *cap, size_t *len);
size_t	ft_count_words_quoted(const char *s);

#endif
