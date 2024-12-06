/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:31:22 by mlazzare          #+#    #+#             */
/*   Updated: 2024/12/06 18:39:20 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(t_pipex **pipex)
{
	t_cmd	*tmp;
	t_cmd	*next;

	close((*pipex)->fd_infile);
	close((*pipex)->fd_outfile);

	if ((*pipex)->cmds)
	{
		tmp = (*pipex)->cmds;
		while (tmp)
		{
			next = tmp->next;
			free(tmp->cmd);
			ft_free_array(tmp->argv);
			free(tmp);
			tmp = next;
		}
	}
	free(*pipex);
}

ft_free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
