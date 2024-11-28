/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:52:19 by mgendrot          #+#    #+#             */
/*   Updated: 2024/11/08 13:40:19 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_put_u(unsigned int n, int fd)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_put_u(n / 10, fd);
		count += ft_put_u(n % 10, fd);
	}
	else
		count += ft_print_c_fd(n + 48, fd);
	return (count);
}

int	ft_print_u_fd(unsigned int n, int fd)
{
	int	count;

	count = 0;
	count += ft_put_u(n, fd);
	if (count < 0)
		return (-1);
	return (count);
}
