/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:51:48 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/07 23:47:32 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*g_pname;
char	**g_envp;

int	main(int argc, char **argv, char **envp)
{
	t_pipex			pipex;
	int				ret_code;

	pipex = (t_pipex){};
	ret_code = RET_OK;
	g_pname = argv[0];
	g_envp = envp;
	if (init_pipex(argc, argv, &pipex) != RET_OK)
		return (free_pipex(&pipex), EXIT_FAILURE);
	dup2(pipex.fd_infile, STDIN_FILENO);
	if (pipex.cmd_count)
		execute_commands(&pipex);
	free_pipex(&pipex);
	return (ret_code);
}
