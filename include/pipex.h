/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:12:09 by mgendrot          #+#    #+#             */
/*   Updated: 2024/11/29 16:37:26 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

# define CMD_PATH "/bin/"



# include <fcntl.h>
# include <sys/wait.h>


int 	pipex(char **argv, char **envp);
void 	first_child(int fd[2], int file1, char *cmd, char **envp);
void 	second_child(int fd[2], int file2, char *cmd, char **envp);
void 	exec_cmd(char *cmd, char **envp);
int 	error(char *msg);
char *find_path(char *cmd, char **envp);

#endif

