/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:01:40 by mgendrot          #+#    #+#             */
/*   Updated: 2024/12/06 19:17:28 by mgendrot         ###   ########.fr       */
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

# define RET_OK 0
# define RET_KO 1

# define PATH 5
# define START 6


# define HERE_DOC					"here_doc"
# define HERE_DOC_TMP_PATH			"/tmp/tmp-heredoc-pipex"
# define HERE_DOC_PREFIX			"here_doc> "



# define ERROR_MISSING_OPERAND		"%s%s:\tMissing operand.\n%s"
# define ERROR_MISSING_ARGS			"%s%s:\tNot enough arguments.\n%s"
# define ERROR_INT					"%s%s:\tInternal error.\n%s"
# define ERROR_PATH					"%s%s:\tCould not find paths in envp.\n%s"
# define ERROR_HERE_DOC_INT			"%s%s:\tInternal error reading here_doc\n%s"
# define ERROR_HERE_DOC_OPEN_TMP	"%s%s:\tError opening here_doc tmp fd\n%s"
# define ERROR_CMD_NOT_FOUND		"%s%s:\tCommand not found: %s.\n%s"
# define ERROR_NO_SUCH_FILE_INPUT	"%s%s:\tNo such file or directory : %s.\n%s"
# define ERROR_INT_PIPE				"%s%s:\tInternal error creating pipe.\n%s"
# define ERROR_INT_FORK				"%s%s:\tInternal error on fork.\n%s"
# define ERROR_CHILD_EXECUTION		"%s%s:\tChild process execution error.\n%s"
# define ERROR_CHILD_WAIT			"%s%s:\tError while waiting for child.\n%s"
# define ERROR_OPEN_OUT				"%s%s:\tError opening out, check perms.\n%s"
# define ERROR_OPEN_TMP_EMPTY		"%s%s:\tCould'nt open /tmp/pipex_empty.\n%s"


extern char	*g_pname;
extern char	**g_envp;

typedef struct s_cmd
{
	int		fd[2];
	char	*cmd;
	char	**argv;
	t_cmd	*next;
}	t_cmd;

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	char	**path;
	size_t	cmd_count;
	t_cmd	**cmds;
}	t_pipex;


// free functions

void	free_pipex(t_pipex **pipex);
void	ft_free_array(char **array);


#endif

