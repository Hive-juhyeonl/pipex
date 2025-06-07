/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:45:52 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/05/17 21:45:54 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_getenv(char *envp[], const char *name)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0
			&& envp[i][len] == '=')
		{
			return (&envp[i][len + 1]);
		}
		i++;
	}
	return (NULL);
}

char	*search_paths(char **paths, char *cmd)
{
	char	*tmp;
	char	*full;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full)
			return (NULL);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

static char	*handle_slash_case(char *cmd)
{
	if (access(cmd, F_OK) != 0)
		error_exit(cmd, 127);
	if (is_directory(cmd))
	{
		if (cmd[0] == '/' || cmd[0] == '.')
			error_exit(cmd, 126);
		error_exit(cmd, 127);
	}
	if (access(cmd, X_OK) != 0)
		error_exit(cmd, 126);
	return (ft_strdup(cmd));
}

char	*find_path(t_pipex *ctx, char *cmd)
{
	char	**paths;
	char	*env_path;
	char	*res;

	if (ft_strchr(cmd, '/'))
		return (handle_slash_case(cmd));
	env_path = ft_getenv(ctx->envp, "PATH");
	if (!env_path || *env_path == '\0')
		error_exit(cmd, 127);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	res = search_paths(paths, cmd);
	ft_free(paths);
	return (res);
}
