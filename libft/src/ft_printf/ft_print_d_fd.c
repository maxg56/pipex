/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:07:12 by mgendrot          #+#    #+#             */
/*   Updated: 2024/11/08 13:40:03 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_ft_print_d(long n, int fd)
{
	if (n >= 10)
		return (ft_print_d_fd(n / 10, fd) + ft_print_d_fd(n % 10, fd));
	return (ft_print_c_fd(n + 48, fd));
}

int	ft_print_d_fd(int n, int fd)
{
	long	_n;

	_n = n;
	if (n < 0)
		return (write(fd, "-", 1) + _ft_print_d(-_n, fd));
	return (_ft_print_d(_n, fd));
}
