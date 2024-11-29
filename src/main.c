/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by mgendrot          #+#    #+#             */
/*   Updated: 2024/11/29 14:04:38 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <sys/wait.h>

int 	main(int argc, char **argv, char **envp) 
{
	if (argc != 5)
		return (write(2, "Invalid arguments\n", 18), 1);
	int		fd[argc - 3];
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		perror("pipe");

	pid1 = fork();
	if (pid1 == 0)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == -1) 
			perror("file1");
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execve(get_cmd_path(argv[2], envp), parse_cmd(argv[2]), envp);
	}

	pid2 = fork();
    if (pid2 == 0)
	{
		outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			perror("file2");
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(fd[1]);
		execve(get_cmd_path(argv[3], envp), parse_cmd(argv[3]), envp);
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
