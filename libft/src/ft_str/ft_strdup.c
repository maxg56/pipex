/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:29:59 by mgendrot          #+#    #+#             */
/*   Updated: 2024/10/23 11:50:15 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*copi;
	int		i;

	i = 0;
	copi = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!copi)
		return (NULL);
	while (src[i])
	{
		copi[i] = src[i];
		i++;
	}
	copi[i] = '\0';
	return (copi);
}
