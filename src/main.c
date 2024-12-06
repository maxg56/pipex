/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:35:14 by mlazzare          #+#    #+#             */
/*   Updated: 2024/12/06 19:04:11 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*g_pname;
char	**g_envp;

int	main(int argc, char **argv, char **envp)
{
	t_pipex			*pipex;

	pipex = malloc(sizeof(t_pipex));
	g_pname = argv[0];
	g_envp = envp;
	if (init_pipex(argc, argv, &pipex) != EXIT_SUCCESS)
		return (free_pipex(&pipex), EXIT_FAILURE);
	dup2(pipex->fd_infile, STDIN_FILENO);
	if ((*pipex->cmds)->next)
		execute_commands(&pipex);
	free_pipex(&pipex);
	return (EXIT_SUCCESS);
}
