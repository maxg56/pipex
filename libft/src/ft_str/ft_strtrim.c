/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:11:29 by mgendrot          #+#    #+#             */
/*   Updated: 2024/10/17 16:27:16 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_setinset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	min;
	size_t	max;
	size_t	len;

	if (!s1)
		return (NULL);
	min = 0;
	while (s1[min] && ft_setinset(s1[min], set))
		min++;
	max = ft_strlen(s1);
	while (min < max && ft_setinset(s1[max - 1], set))
		max--;
	len = max - min;
	return (ft_substr(s1, min, len));
}
