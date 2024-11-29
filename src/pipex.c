/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:25:57 by mgendrot          #+#    #+#             */
/*   Updated: 2024/11/29 16:30:06 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(char **argv, char **envp) 
{
	int	fd[2];
	int	file1;
	int	file2;

	file1 = open(argv[1], O_RDONLY);
	if (file1 < 0)
		return (error("Error opening file1"));
	file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 < 0)
		return (error("Error opening file2"));

	if (pipe(fd) < 0)
		return (error("Pipe error"));
	if (fork() == 0)
		first_child(fd, file1, argv[2], envp);
	if (fork() == 0)
		second_child(fd, file2, argv[3], envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	return (0);
}
