/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:08:39 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/09 19:49:24 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_format(const char *error_format, const char *detail)
{
	ft_dprintf(STDERR_FILENO, error_format,
		TERM_RED,
		g_pname,
		detail,
		TERM_RESET);
}

void	print_error(const char *error_format)
{
	ft_dprintf(STDERR_FILENO, error_format,
		TERM_RED,
		g_pname,
		TERM_RESET);
}

void	print_cmd_not_found_error(const char *cmd)
{
	print_format(ERROR_CMD_NOT_FOUND, cmd);
}

void	print_no_such_file_error(const char *file)
{
	print_format(ERROR_NO_SUCH_FILE_INPUT, file);
}
