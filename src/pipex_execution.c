/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:35:18 by mgendrot          #+#    #+#             */
/*   Updated: 2024/12/10 03:23:14 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_ret	handle_child_status(int child_status, char *cmd_name)
{
	if (child_status == 127)
		return (print_cmd_not_found_error(cmd_name), RET_ERR);
	return (RET_OK);
}

static void	setup_command_output(t_pipex *pipex, int cmd_idx, int p_fd[2])
{
	close(p_fd[0]);
	if (cmd_idx == (int)(pipex->cmd_count - 1))
		(close(p_fd[1]), dup2(pipex->fd_outfile, STDOUT_FILENO));
	else
		(dup2(p_fd[1], STDOUT_FILENO), close(p_fd[1]));
}

static void	execute_command(t_pipex *pipex, int cmd_idx, int p_fd[2])
{
	char	*cmd_path;

	setup_command_output(pipex, cmd_idx, p_fd);
	close(pipex->fd_outfile);
	close(pipex->fd_infile);
	cmd_path = get_absolute_path(
			pipex->cmd[cmd_idx].argv[0],
			pipex->paths
			);
	if (!cmd_path)
		(free_pipex(pipex), _exit(127));
	if (execve(cmd_path, pipex->cmd[cmd_idx].argv, g_envp) == -1)
		(free_pipex(pipex), _exit(126));
}

static t_ret	do_command_pipe(t_pipex *pipex, int cmd_idx)
{
	pid_t	cmd_pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		return (print_error(ERROR_INT_PIPE), RET_ERR);
	cmd_pid = fork();
	if (cmd_pid == -1)
		return (print_error(ERROR_INT_FORK), RET_ERR);
	if (!cmd_pid)
		execute_command(pipex, cmd_idx, p_fd);
	else
	{
		pipex->pid_list[cmd_idx] = cmd_pid;
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
	}
	return (RET_OK);
}

t_ret	execute_commands(t_pipex *pipex)
{
	unsigned int	i;
	int				exit_status;
	int				ret_code;

	ret_code = RET_OK;
	i = 0;
	while (i < pipex->cmd_count)
	{
		if (do_command_pipe(pipex, i) != RET_OK)
			return (free_pipex(pipex), RET_ERR);
		i++;
	}
	i = -1;
	while (++i < pipex->cmd_count)
	{
		waitpid(pipex->pid_list[i], &exit_status, 0);
		if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status))
			ret_code = handle_child_status(WEXITSTATUS(exit_status),
					pipex->cmd[i].argv[0]);
	}
	if (pipex->pid_list[i - 1] == -1)
		return (free_pipex(pipex), RET_ERR);
	if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status))
		return (WEXITSTATUS(exit_status));
	return (ret_code);
}
