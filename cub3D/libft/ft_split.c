/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:32:32 by alexandreme       #+#    #+#             */
/*   Updated: 2025/02/23 20:16:35 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordlen(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_wordcount(char *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			wcount++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (wcount);
}

static char	*allocate_word(const char *s, char c)
{
	int		wlen;
	char	*word;
	int		i;

	wlen = ft_wordlen((char *)s, c);
	word = malloc(sizeof(char) * (wlen + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < wlen)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**free_split(char **res, int j)
{
	while (j >= 0)
		free(res[j--]);
	free(res);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	int		j;
	int		wcount;
	char	**res;

	if (!s)
		return (NULL);
	wcount = ft_wordcount((char *)s, c);
	res = malloc(sizeof(char *) * (wcount + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (j < wcount)
	{
		while (*s && *s == c)
			s++;
		res[j] = allocate_word(s, c);
		if (!res[j])
			free_split(res, j - 1);
		s += ft_wordlen((char *)s, c);
		j++;
	}
	res[j] = NULL;
	return (res);
}
