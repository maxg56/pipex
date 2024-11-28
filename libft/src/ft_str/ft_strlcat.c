/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:12:53 by mgendrot          #+#    #+#             */
/*   Updated: 2024/10/17 16:17:46 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i_d;
	size_t	i_s;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	i_d = ft_strlen(dst);
	i_s = 0;
	while (src[i_s] && i_d + 1 < dstsize)
	{
		dst[i_d] = src[i_s];
		i_d++;
		i_s++;
	}
	dst[i_d] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i_s]));
}
