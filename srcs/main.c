/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:45:57 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/05/17 21:45:58 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	clean_pipex(t_pipex *ctx)
{
	ft_free(ctx->cmd1);
	ft_free(ctx->cmd2);
}

void	init_pipex(t_pipex *ctx)
{
	ctx->cmd1 = ft_split(ctx->av[2], ' ');
	ctx->cmd2 = ft_split(ctx->av[3], ' ');
	if (!ctx->cmd1 || !ctx->cmd2)
		error_exit("malloc", 1);
	if (pipe(ctx->fd) < 0)
		error_exit("pipe", 1);
}

void	run_pipeline(t_pipex *ctx)
{
	ctx->pid1 = fork();
	if (ctx->pid1 < 0)
		error_exit("fork", 1);
	if (ctx->pid1 == 0)
		child_process1(ctx);
	ctx->pid2 = fork();
	if (ctx->pid2 < 0)
		error_exit("fork", 1);
	if (ctx->pid2 == 0)
		child_process2(ctx);
	close(ctx->fd[0]);
	close(ctx->fd[1]);
	waitpid(ctx->pid1, &ctx->status1, 0);
	waitpid(ctx->pid2, &ctx->status2, 0);
	if (WIFEXITED(ctx->status2))
		ctx->status_code = WEXITSTATUS(ctx->status2);
	else if (WIFSIGNALED(ctx->status2))
		ctx->status_code = 128 + WTERMSIG(ctx->status2);
	else if (WIFEXITED(ctx->status1))
		ctx->status_code = WEXITSTATUS(ctx->status1);
	else if (WIFSIGNALED(ctx->status1))
		ctx->status_code = 128 + WTERMSIG(ctx->status1);
	else
		ctx->status_code = 1;
	clean_pipex(ctx);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	ctx;

	ctx.ac = ac;
	ctx.av = av;
	ctx.envp = envp;
	if (ac != 5)
		error_exit("usage: ./pipex infile cmd1 cmd2 outfile", 1);
	init_pipex(&ctx);
	run_pipeline(&ctx);
	return (ctx.status_code);
}
