/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pathing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:33:45 by mgendrot          #+#    #+#             */
/*   Updated: 2024/12/11 22:21:40 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*handle_relative_command(char *command)
{
	if (access(command, F_OK | X_OK) == 0)
		return (command);
	return (NULL);
}

char	**get_paths(void)
{
	char	**envp;
	char	*path;

	envp = g_envp;
	while (*envp)
	{
		if (ft_strncmp(*envp, ENVP_PATH, sizeof(ENVP_PATH) - 1) == 0)
		{
			path = (*envp) + sizeof(ENVP_PATH) - 1;
			return (ft_split(path, ENVP_PATH_SEPARATOR));
		}
		++envp;
	}
	return (NULL);
}

char	*get_absolute_path(char *command, char **paths)
{
	char	*res;

	if (ft_strchr(command, '/'))
		return (handle_relative_command(command));
	while (*paths)
	{
		res = ft_strjoin3(*paths, "/", command);
		if (!res)
			return (NULL);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
		++paths;
	}
	return (NULL);
}
