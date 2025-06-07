/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:45:44 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/05/17 21:45:46 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*get_path(t_pipex *ctx, char *cmd_path)
{
	char	*path;

	if (ft_strchr(cmd_path, '/'))
	{
		path = ft_strdup(cmd_path);
		if (!path)
			error_exit("malloc", 1);
		if (access(path, X_OK) != 0)
		{
			free(path);
			if (errno == EACCES)
				error_exit(cmd_path, 126);
			else
				error_exit(cmd_path, 127);
		}
	}
	else
	{
		path = find_path(ctx, cmd_path);
		if (!path)
			error_exit(NULL, 127);
		if (is_directory(path))
			error_exit(cmd_path, 127);
	}
	return (path);
}

// r = raw (there was line too long....so...I changed it to r...)
void	execute(t_pipex *ctx, int cmd_num)
{
	char	**cmd;
	char	*path;

	if (strchr(ctx->r, '"') || strchr(ctx->r, '\'') || strchr(ctx->r, '\\'))
	{
		cmd = ft_split_quoted(ctx->r);
		if (!cmd || !cmd[0] || cmd[0][0] == '\0')
			error_exit("malloc", 1);
	}
	else
	{
		if (cmd_num == 1)
			cmd = ctx->cmd1;
		else
			cmd = ctx->cmd2;
		if (!cmd || !cmd[0] || cmd[0][0] == '\0')
			error_exit(NULL, 127);
	}
	path = get_path(ctx, cmd[0]);
	execve(path, cmd, ctx->envp);
	if (errno == EACCES)
		error_exit(path, 126);
	else
		error_exit(cmd[0], 127);
}
