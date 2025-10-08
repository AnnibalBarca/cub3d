/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:42:39 by almeekel          #+#    #+#             */
/*   Updated: 2025/02/23 19:58:54 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_read(int fd, char *cup, char **basin)
{
	ssize_t	bytes;
	char	*tmp;

	bytes = read(fd, cup, BUFFER_SIZE);
	if (bytes < 0)
		return (-1);
	if (bytes == 0)
		return (0);
	cup[bytes] = '\0';
	tmp = ft_strjoin_g(*basin, cup);
	if (!tmp)
		return (-1);
	free(*basin);
	*basin = tmp;
	return (bytes);
}

static char	*extract_line(char *basin)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!basin)
		return (NULL);
	while (basin[i] && basin[i] != '\n')
		i++;
	line = ft_substr_g(basin, 0, i + (basin[i] == '\n'));
	return (line);
}

static char	*update_basin(char *basin)
{
	size_t	i;
	char	*newb;

	i = 0;
	if (!basin)
		return (NULL);
	while (basin[i] && basin[i] != '\n')
		i++;
	if (!basin[i])
	{
		free(basin);
		return (NULL);
	}
	newb = ft_substr_g(basin, i + 1, ft_strlen_g(basin + i + 1));
	free(basin);
	return (newb);
}

static int	gnl_loop(int fd, char **basin)
{
	ssize_t	bytes;
	char	*cup;

	bytes = 1;
	cup = malloc(BUFFER_SIZE + 1);
	if (!cup)
		return (-1);
	while (!ft_strchr_g(*basin, '\n') && bytes > 0)
	{
		bytes = handle_read(fd, cup, basin);
		if (bytes < 0)
		{
			free(cup);
			return (-1);
		}
	}
	free(cup);
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*basin;
	char		*line;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!basin)
	{
		basin = ft_strdup_g("");
		if (!basin)
			return (NULL);
	}
	status = gnl_loop(fd, &basin);
	if (status < 0 || !basin || !*basin)
		return (free(basin), basin = NULL, NULL);
	line = extract_line(basin);
	if (!line)
		return (free(basin), basin = NULL, NULL);
	basin = update_basin(basin);
	if (!basin)
		return (line);
	return (line);
}
