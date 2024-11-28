/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:07:29 by mgendrot          #+#    #+#             */
/*   Updated: 2024/10/25 11:44:55 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c);
static int	ft_strlen_c(char *str, char c);
static char	**free_arr(int i, char **arr);

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	int		words;
	char	**split;

	if (!s)
		return (NULL);
	i = 0;
	words = count_word(s, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	while (i < words)
	{
		while (*s == c && *s)
			s++;
		len = ft_strlen_c((char *) s, c);
		split[i] = ft_substr(s, 0, len);
		if (!split[i])
			return (free_arr(i, split));
		s += len;
		i++;
	}
	split[i] = NULL;
	return (split);
}

static int	count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_strlen_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	**free_arr(int i, char **split)
{
	while (i > 0)
		free(split[--i]);
	free(split);
	return (NULL);
}
