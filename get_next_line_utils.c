/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jna <jna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 00:20:10 by jna               #+#    #+#             */
/*   Updated: 2021/01/22 05:39:08 by jna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_newline(char **str)
{
	int			newline;

	newline = 0;
	while (*(*str + newline))
	{
		if (*(*str + newline) == '\n')
			return (newline);
		newline++;
	}
	return (-1);
}

size_t	ft_strlen(const char *s)
{
	unsigned int	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	count;

	count = 0;
	if (dst == NULL || src == NULL)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[count] && count < dstsize - 1)
	{
		dst[count] = src[count];
		count++;
	}
	if (dstsize != 0)
		dst[count] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(char *str)
{
	char			*strdup;

	if (str == NULL)
		return (0);
	if (!(strdup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (0);
	ft_strlcpy(strdup, str, (ft_strlen(str) + 1));
	return (strdup);
}
