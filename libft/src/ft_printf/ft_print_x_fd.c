/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:59:18 by mgendrot          #+#    #+#             */
/*   Updated: 2024/11/08 13:40:49 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_put_hex(unsigned int n, char *chars, int fd)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += ft_put_hex(n / 16, chars, fd);
		count += ft_put_hex(n % 16, chars, fd);
	}
	else
		count += ft_print_c_fd(chars[n], fd);
	return (count);
}

int	ft_print_x_fd(unsigned int n, int format, int fd)
{
	char	*chars;

	if (format == 'x')
		chars = "0123456789abcdef";
	else
		chars = "0123456789ABCDEF";
	return (ft_put_hex(n, chars, fd));
}
