/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:37:20 by mgendrot          #+#    #+#             */
/*   Updated: 2024/12/10 01:05:18 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_ret	redirect_in_to_empty(t_pipex *pipex)
{
	pipex->fd_infile = open(TMP_EMPTY_PATH, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (pipex->fd_infile < 0)
		return (print_error(ERROR_OPEN_TMP_EMPTY), RET_ERR);
	return (RET_OK);
}

static t_ret	handle_in_out_fd(int argc, char **argv,
			t_pipex *pipex, int out_flags)
{
	if (pipex->fd_infile < 0)
		(print_no_such_file_error(argv[1]), redirect_in_to_empty(pipex));
	if (pipex->fd_infile < 0)
		return (RET_ERR);
	pipex->fd_outfile = open (argv[argc - 1], out_flags, 0666);
	if (pipex->fd_outfile < 0)
		return (print_error(ERROR_OPEN_OUT), RET_ERR);
	return (RET_OK);
}

static t_ret	parse_commands(char **argv, t_pipex *pipex)
{
	unsigned int	curr_cmd;

	curr_cmd = 0;
	pipex->cmd = malloc(sizeof(t_cmd) * pipex->cmd_count);
	if (!pipex->cmd)
		return (free_pipex(pipex), print_error(ERROR_INT), RET_ERR);
	while (curr_cmd < pipex->cmd_count)
	{
		pipex->cmd[curr_cmd].argv = ft_split(argv[curr_cmd], ' ');
		if (!pipex->cmd[curr_cmd++].argv)
			return (free_pipex(pipex), print_error(ERROR_INT), RET_ERR);
	}
	return (RET_OK);
}

t_ret	parse_input(int argc, char **argv, t_pipex *pipex)
{
	int	here_doc;
	int	out_flags;

	if (argc < 2)
		return (print_error(ERROR_MISSING_ARGS), RET_ERR);
	here_doc = ft_strncmp(argv[1], HERE_DOC, 9) == 0;
	pipex->cmd_count = argc - (3 + here_doc);
	if (argc - (3 + here_doc * 2) < 0)
		return (print_error(ERROR_MISSING_ARGS), RET_ERR);
	out_flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (here_doc)
	{
		if (read_here_doc(argv[2], pipex) != RET_OK)
			return (RET_ERR);
		out_flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	else
		pipex->fd_infile = open(argv[1], O_RDONLY);
	if (handle_in_out_fd(argc, argv, pipex, out_flags) != RET_OK)
		return (RET_ERR);
	return (parse_commands(argv + 2 + here_doc, pipex));
}
