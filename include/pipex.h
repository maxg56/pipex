/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:01:40 by mgendrot          #+#    #+#             */
/*   Updated: 2024/12/07 16:28:28 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


// Includes

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
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

# define BUFFER_SIZE				4096

# define RET_OK						0
# define RET_ERR					1
# define RET_CMD_NOT_FOUND			127
# define RET_EXECUTION_ERROR		126

# define PIPE_READ					0
# define PIPE_WRITE					1

// Paths

# define ENVP_PATH					"PATH="
# define ENVP_PATH_SEPARATOR		':'
# define TMP_EMPTY_PATH				"/tmp/pipex_empty"

// Global variable

// Holds the program name
extern char	*g_pname;
extern char	**g_envp;

// Structures

typedef struct s_command
{
	char	**argv;
}	t_command;

typedef struct s_pipex
{
	int			fd_infile;
	int			fd_outfile;
	char		**paths;
	size_t		cmd_count;
	t_command	*commands;
	int			*pid_list;
}	t_pipex;

// Functions

// Error functions

void	print_gen_error(const char *error);
void	print_cmd_not_found_error(const char *cmd);
void	print_no_such_file_error(const char *file);

// Structure handling functions

void	free_double_tab(char	***arr);
void	free_pipex(t_pipex *pipex);
void	free_commands(t_pipex *pipex);
int		init_pipex(int argc, char **argv, t_pipex *pipex);

// Fd handling functions

int		handle_in_out_fd(int argc, char **argv, t_pipex *pipex, int out_flags);
int		redirect_in_to_empty(t_pipex *pipex);

// Path functions

char	**get_paths(void);
char	*get_absolute_path(char *command, char **paths);
char	*handle_relative_command(char *command);

// Parsing functions

int		parse_input(int argc, char **argv, t_pipex *pipex);
int		parse_commands(char **argv, t_pipex *pipex);

// Here_doc function

int		read_here_doc(const char *limiter, t_pipex *pipex);

// Execution

int		do_command_pipe(t_pipex *pipex, int cmd_idx);
void	execute_command(t_pipex *pipex, int cmd_idx, int p_fd[2]);
int		handle_child_status(int child_status, char *cmd_name);
int		execute_commands(t_pipex *pipex);

#endif

