/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pathing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:33:45 by mgendrot          #+#    #+#             */
/*   Updated: 2024/12/10 01:02:40 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*res;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	res = malloc(len1 + len2 + len3 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	ft_memcpy(res + len1 + len2, s3, len3 + 1);
	return (res);
}

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

	if (ft_strncmp(command, "./", 2) == 0)
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
