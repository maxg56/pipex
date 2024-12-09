/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:01:40 by mgendrot          #+#    #+#             */
/*   Updated: 2024/12/09 20:30:37 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


// Includes

# include "libft.h"

# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

// Terminal colors

# define TERM_RESET					"\033[0m"
# define TERM_BLACK					"\033[30m"
# define TERM_RED					"\033[31m"
# define TERM_GREEN					"\033[32m"
# define TERM_YELLOW				"\033[33m"
# define TERM_BLUE					"\033[34m"
# define TERM_MAGENTA				"\033[35m"
# define TERM_CYAN					"\033[36m"
# define TERM_WHITE					"\033[37m"

# define TERM_UP					"\033[1A"
# define TERM_CLEAR_LINE			"\033[2K\r"

// Here doc constants

# define HERE_DOC					"here_doc"
# define HERE_DOC_TMP_PATH			"/tmp/tmp-heredoc-pipex"
# define HERE_DOC_PREFIX			"here_doc> "

// Error messages

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

// Utils define

# define PIPE_READ					0
# define PIPE_WRITE					1

typedef enum e_ret
{
	RET_OK = 0,
	RET_ERR = 1,
	RET_CMD_NOT_FOUND = 127,
	RET_EXECUTION_ERROR = 126
}	t_ret;


// Paths

# define ENVP_PATH					"PATH="
# define ENVP_PATH_SEPARATOR		':'
# define TMP_EMPTY_PATH				"/tmp/pipex_empty"

// Holds the program name

extern char	*g_pname;
extern char	**g_envp;

// Structures

typedef struct s_cmd
{
	char	**argv;
}	t_cmd;

typedef struct s_pipex
{
	int			fd_infile;
	int			fd_outfile;
	char		**paths;
	size_t		cmd_count;
	int			*pid_list;
	t_cmd		*commands;
}	t_pipex;

// Error handling functions

void	print_error(const char *error_format);
void	print_cmd_not_found_error(const char *cmd);
void	print_no_such_file_error(const char *file);

// Structure handling functions

t_ret	init_pipex(int argc, char **argv, t_pipex *pipex);
void	free_pipex(t_pipex *pipex);
void	free_commands(t_pipex *pipex);


// Path functions

char	**get_paths(void);
char	*get_absolute_path(char *command, char **paths);

// Parsing functions

t_ret	parse_input(int argc, char **argv, t_pipex *pipex);

// Here_doc function

t_ret	read_here_doc(const char *limiter, t_pipex *pipex);

// Execution

void	execute_command(t_pipex *pipex, int cmd_idx, int p_fd[2]);
t_ret	execute_commands(t_pipex *pipex);

#endif

