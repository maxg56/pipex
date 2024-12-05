/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:31:22 by mlazzare          #+#    #+#             */
/*   Updated: 2024/12/05 04:04:45 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_arr(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	if (path)
		free(path);
	return (0);
}

void	free_struct(t_cmd *c)
{
	int	i;

	i = 0;
	if (c->cmd)
		free(c->cmd);
	free_arr(c->path);
	while (c->args[i])
		free(c->args[i++]);
}

int	check_empty(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != ' ')
			return (0);
	}
	ft_dprintf(2, "-bash: %s : command not found\n", s);
	return (1);
}

void	error_msg(char *c)
{
	write(2, "-bash: ", 7);
	write(2, c, ft_strlen(c));
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
}
