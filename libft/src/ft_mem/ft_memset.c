/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:49:46 by mgendrot          #+#    #+#             */
/*   Updated: 2024/10/23 16:32:26 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count )
{
	char	*str;

	str = pointer;
	while (count)
	{
		*str = (unsigned char)value;
		str++;
		count--;
	}
	return (pointer);
}
