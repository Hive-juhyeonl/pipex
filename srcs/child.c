/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:45:22 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/05/17 21:45:25 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process1(t_pipex *ctx)
{
	if (!ctx->av[1] || ctx->av[1][0] == '\0')
	{
		write(2, "no such file or directory\n", 26);
		exit(1);
	}
	ctx->infile = open(ctx->av[1], O_RDONLY);
	if (ctx->infile < 0)
		error_exit(ctx->av[1], 1);
	if (dup2(ctx->infile, STDIN_FILENO) < 0)
		error_exit("dup2", 1);
	if (dup2(ctx->fd[1], STDOUT_FILENO) < 0)
		error_exit("dup2", 1);
	close(ctx->fd[0]);
	close(ctx->fd[1]);
	ctx->r = ctx->av[2];
	execute(ctx, 1);
}

void	child_process2(t_pipex *ctx)
{
	if (!ctx->av[4] || ctx->av[4][0] == '\0')
	{
		write(2, "no such file or directory\n", 26);
		exit(1);
	}
	ctx->outfile = open(ctx->av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ctx->outfile < 0)
		error_exit(ctx->av[4], 1);
	if (dup2(ctx->fd[0], STDIN_FILENO) < 0)
		error_exit("dup2", 1);
	if (dup2(ctx->outfile, STDOUT_FILENO) < 0)
		error_exit("dup2", 1);
	close(ctx->fd[0]);
	close(ctx->fd[1]);
	ctx->r = ctx->av[3];
	execute(ctx, 2);
}
