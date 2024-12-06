/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:32:10 by mgendrot          #+#    #+#             */
/*   Updated: 2024/12/06 15:39:31 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printchar_fd(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

static int	ft_formats(va_list args, const char format, int fd)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_print_c_fd(va_arg(args, int), fd);
	else if (format == 's')
		print_length += ft_print_s_fd(va_arg(args, char *), fd);
	else if (format == 'p')
		print_length += ft_print_p_fd(va_arg(args, uintptr_t), fd);
	else if (format == 'd' || format == 'i')
		print_length += ft_print_d_fd(va_arg(args, int), fd);
	else if (format == 'u')
		print_length += ft_print_u_fd(va_arg(args, unsigned int), fd);
	else if (format == 'x' || format == 'X')
		print_length += ft_print_x_fd(va_arg(args, unsigned int), format, fd);
	else if (format == '%')
		print_length += ft_print_pct_fd(fd);
	return (print_length);
}

int	ft_dprintf( int fd, const char *str, ...)
{
	int		i;
	va_list	args;
	int		print_length;

	i = 0;
	print_length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_length += ft_formats(args, str[i + 1], fd);
			i++;
		}
		else
			print_length += ft_printchar_fd(str[i], fd);
		i++;
	}
	va_end(args);
	return (print_length);
}