/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:05:22 by mgendrot          #+#    #+#             */
/*   Updated: 2024/11/08 13:30:46 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar_fd(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_formats(va_list args, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_print_c_fd(va_arg(args, int), FD);
	else if (format == 's')
		print_length += ft_print_s_fd(va_arg(args, char *), FD);
	else if (format == 'p')
		print_length += ft_print_p_fd(va_arg(args, uintptr_t), FD);
	else if (format == 'd' || format == 'i')
		print_length += ft_print_d_fd(va_arg(args, int), FD);
	else if (format == 'u')
		print_length += ft_print_u_fd(va_arg(args, unsigned int), FD);
	else if (format == 'x' || format == 'X')
		print_length += ft_print_x_fd(va_arg(args, unsigned int), format, FD);
	else if (format == '%')
		print_length += ft_print_pct_fd(FD);
	return (print_length);
}

int	ft_printf(const char *str, ...)
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
			print_length += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			print_length += ft_printchar_fd(str[i], FD);
		i++;
	}
	va_end(args);
	return (print_length);
}
