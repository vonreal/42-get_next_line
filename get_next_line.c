/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jna <jna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 00:10:33 by jna               #+#    #+#             */
/*   Updated: 2021/01/22 17:01:05 by jna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		append_backup(char **backup, char **buf, int read_size)
{
	char		*temp;
	int			size;

	if (*backup == NULL)
		*backup = ft_strdup(*buf);
	else
	{
		temp = *backup;
		size = ft_strlen(temp) + read_size;
		if (!(*backup = (char *)malloc(sizeof(char) * (size + 1))))
		{
			free(*buf);
			free(temp);
			temp = NULL;
			return (-1);
		}
		ft_strlcpy(*backup, temp, (ft_strlen(temp) + 1));
		ft_strlcpy(*backup + ft_strlen(temp), *buf, (ft_strlen(*buf) + 1));
		free(temp);
		temp = NULL;
	}
	return (0);
}

int		set_backup(char **backup, int newline)
{
	char		*temp;
	int			size;

	if (ft_strlen(*backup + (newline + 1)) == 0)
	{
		free(*backup);
		*backup = NULL;
	}
	else
	{
		temp = *backup;
		size = ft_strlen(temp) - (newline + 1);
		if (!(*backup = (char *)malloc(sizeof(char) * (size + 1))))
		{
			free(temp);
			temp = NULL;
			return (-1);
		}
		ft_strlcpy(*backup, &temp[newline + 1], (size + 1));
		free(temp);
		temp = NULL;
	}
	return (1);
}

int		return_line(char **backup, int newline, char **line)
{
	int			size;
	char		*one_line;

	size = ft_strlen(*backup) - ft_strlen(*backup + newline);
	if (!(one_line = (char *)malloc(sizeof(char) * (size + 1))))
	{
		free(backup);
		backup = NULL;
		return (-1);
	}
	ft_strlcpy(one_line, *backup, (size + 1));
	*line = one_line;
	return (set_backup(backup, newline));
}

int		last_return(char **backup, char **buf, char **line, int read_size)
{
	int			newline;

	free(*buf);
	if (read_size < 0)
		return (-1);
	if (*backup == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	if ((newline = get_newline(backup)) >= 0)
		return (return_line(backup, newline, line));
	*line = ft_strdup(*backup);
	free(*backup);
	*backup = NULL;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*backup;
	char		*buf;
	int			read_size;
	int			newline;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		if (append_backup(&backup, &buf, read_size) < 0)
		{
			free(backup);
			return (-1);
		}
		if ((newline = get_newline(&backup)) >= 0)
		{
			free(buf);
			return (return_line(&backup, newline, line));
		}
	}
	return (last_return(&backup, &buf, line, read_size));
}
