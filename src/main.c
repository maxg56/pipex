/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by mgendrot          #+#    #+#             */
/*   Updated: 2024/11/29 16:24:57 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_dprintf(2, "Usage: ./pipex file1 \"cmd1\" \"cmd2\" file2\n");
		return (1);
	}
	return (pipex(argv, envp));
}
