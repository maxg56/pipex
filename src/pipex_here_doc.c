/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:50:23 by mgendrot          #+#    #+#             */
/*   Updated: 2024/12/09 20:44:14 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_ret	read_here_doc(const char *limiter, t_pipex *pipex)
{
	char	*line;

	pipex->fd_infile = open(HERE_DOC_TMP_PATH,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_infile < 0)
		return (print_error(ERROR_HERE_DOC_OPEN_TMP), RET_ERR);
	ft_printf(HERE_DOC_PREFIX);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter) - 1))
	{
		ft_dprintf(pipex->fd_infile, line);
		(ft_printf(HERE_DOC_PREFIX), free(line));
		line = get_next_line(STDIN_FILENO);
	}
	(free(line), close(pipex->fd_infile));
	pipex->fd_infile = open(HERE_DOC_TMP_PATH, O_RDONLY, 0666);
	if (pipex->fd_infile < 0)
		return (print_error(ERROR_HERE_DOC_OPEN_TMP), RET_ERR);
	return (RET_OK);
}
