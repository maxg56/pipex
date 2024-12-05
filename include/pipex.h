/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:01:40 by mgendrot          #+#    #+#             */
/*   Updated: 2024/12/05 18:03:20 by mgendrot         ###   ########.fr       */
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
# include <errno.h>
# include <string.h>

# define PATH 5
# define START 6

typedef struct s_cmd
{
	char	*cmd;
	char	**path;
	char	*args[100];
	int		f;
}	t_cmd;

void	pipex(int f1, int f2, char **ag, char **ep);
void	exec_cmd(t_cmd *cmd1, t_cmd *cmd2, char **envp);
void	error_msg(char *c);
int		check_cmd(t_cmd *c);
int		check_empty(char *s);

/*
* STRING UTILS
*/

char	**ft_splitpath(char *s, char c);
int		ft_putstr(char *s, char *t);

/*
* FREE
*/

int		free_arr(char **path);
void	free_struct(t_cmd *c);

#endif
