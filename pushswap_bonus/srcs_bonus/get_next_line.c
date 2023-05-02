/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetezea <jmetezea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:12:04 by jmetezea          #+#    #+#             */
/*   Updated: 2023/04/18 18:16:27 by kaly             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

char	*ft_join(char *stash, char *buf)
{
	char	*tmp;

	if (stash)
	{
		tmp = ft_strjoin(stash, buf);
		free(stash);
	}
	else
		tmp = ft_strdup(buf);
	return (tmp);
}

char	*ft_read(int fd, char *stash)
{
	char	*buf;
	ssize_t	ret_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	ft_bzero(buf, BUFFER_SIZE + 1);
	ret_read = 1;
	while (ret_read > 0 && !(ft_isnewline(stash)))
	{
		ret_read = read(fd, buf, BUFFER_SIZE);
		if (ret_read < 0)
		{
			free(buf);
			return (NULL);
		}
		if (ret_read == 0)
			break ;
		stash = ft_join(stash, buf);
		ft_bzero(buf, BUFFER_SIZE);
	}
	free(buf);
	return (stash);
}

char	*ft_extract(char *stash)
{
	char	*out;
	size_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	out = (char *)malloc(sizeof(char) * (i + 2));
	if (!out)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		out[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		out[i] = '\n';
		i++;
	}
	out[i] = 0;
	return (out);
}

char	*ft_clear(char *stash)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n' && stash[i + 1])
	{
		tmp = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
		ft_bzero(tmp, ft_strlen(stash) - i + 1);
		if (!tmp)
			return (NULL);
		j = 0;
		while (stash[++i])
			tmp[j++] = stash[i];
		free(stash);
		return (tmp);
	}
	free(stash);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stash[fd] = ft_read(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_extract(stash[fd]);
	stash[fd] = ft_clear(stash[fd]);
	return (line);
}
