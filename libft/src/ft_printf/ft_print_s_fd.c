/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:47:35 by mgendrot          #+#    #+#             */
/*   Updated: 2024/11/15 13:07:20 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define NULL_STR "(null)"

int	ft_print_s_fd(char *s, int fd)
{
	if (!s)
		return (write(fd, NULL_STR, ft_strlen(NULL_STR)));
	return (write(fd, s, ft_strlen(s)));
}
