/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachhoub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:48:47 by aachhoub          #+#    #+#             */
/*   Updated: 2022/10/24 15:55:39 by aachhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		buff[BUFFER_SIZE + 1];
	int			len;
	int			nl;

	if (!tmp)
		tmp = ft_strdup("");
	len = read(fd, buff, BUFFER_SIZE);
	while (len >= 0)
	{
		buff[len] = 0;
		tmp = ft_strjoin(tmp, buff);
		nl = check_newline(tmp);
		if (nl != -1)
			return (get_current_line(&tmp, nl));
		if (!len && !tmp[0])
			break ;
		if (!len)
			return (get_rest(&tmp, 0));
		len = read(fd, buff, BUFFER_SIZE);
	}
	free(tmp);
	tmp = NULL;
	return (NULL);
}

char	*get_current_line(char **tmp, int nl)
{
	char	*line;

	line = ft_substr(*tmp, 0, nl + 1);
	*tmp = get_rest(tmp, nl + 1);
	return (line);
}

char	*get_rest(char **str, int nl)
{
	char	*reminder;
	int		rlen;

	rlen = ft_strlen(*str + nl);
	reminder = ft_substr(*str, nl, rlen);
	free(*str);
	*str = NULL;
	return (reminder);
}

int	check_newline(char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}
