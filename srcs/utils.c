/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:46:12 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/05/17 21:46:18 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	print_error(char *msg, int exit_code)
{
	if (exit_code == 127)
	{
		if (msg && strchr(msg, '/'))
			write(2, "no such file or directory\n", 26);
		else
			write(2, "command not found\n", 18);
	}
	else if (exit_code == 126)
	{
		if (msg[0] == '/' || msg[0] == '.')
			write(2, "is a directory\n", 16);
		else
			write(2, "permission denied\n", 18);
	}
}

void	error_exit(char *msg, int exit_code)
{
	char	*err;

	if (msg && msg[0])
	{
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
	}
	if (exit_code == 127 || exit_code == 126)
		print_error(msg, exit_code);
	else
	{
		err = strerror(exit_code);
		write(2, err, ft_strlen(err));
		write(2, "\n", 1);
	}
	exit(exit_code);
}

int	is_directory(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	ft_isspace(int c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r');
}
