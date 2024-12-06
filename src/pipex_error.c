/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:02:46 by mgendrot          #+#    #+#             */
/*   Updated: 2024/12/06 17:26:59 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_cmd_not_found_error(const char *cmd)
{
	ft_dprintf(STDERR_FILENO, ERROR_CMD_NOT_FOUND,
		RED,
		g_pname,
		cmd,
		DEF_COLOR
		);
}

void	print_no_such_file_error(const char *file)
{
	ft_dprintf(STDERR_FILENO, ERROR_NO_SUCH_FILE_INPUT,
		RED,
		g_pname,
		file,
		DEF_COLOR
		);
}

void	print_gen_error(const char *error)
{
	ft_dprintf(STDERR_FILENO, error,
		RED,
		g_pname,
		DEF_COLOR
		);
}
