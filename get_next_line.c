/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jna <jna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 00:10:33 by jna               #+#    #+#             */
/*   Updated: 2021/01/22 00:10:33 by jna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		append_backup(char **backup, char **buf, int read_size)
{
	char		*temp;

	if (*backup == NULL)
		*backup = ft_strdup(*buf);
	else
	{
		temp = *backup;
		if (!(*backup = (char *)malloc(sizeof(char) * (ft_strlen(temp) + read_size + 1))))
			return (-1);
		ft_strlcpy(*backup, temp, (ft_strlen(temp) + 1));
		ft_strlcpy(*backup + ft_strlen(temp), *buf, (ft_strlen(*buf) + 1));
		free(temp);
		temp = NULL;
	}
}

int		get_next_line(int fd, char **line)
{
	static char	*backup;
	char		*buf;
	int			read_size;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (append_backup(&backup, &buf, read_size) < 0)
			return (-1);
		*line = ft_strdup(backup);
		return (1);
	}
	free(buf);
	if (read_size < 0)
		return (-1);
	return (0);
}