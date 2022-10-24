/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachhoub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:23:10 by aachhoub          #+#    #+#             */
/*   Updated: 2022/10/24 15:55:25 by aachhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*tmp[1024];
	char		buff[BUFFER_SIZE + 1];
	char		*line;
	int			ret;
	int			nl;

	if (!tmp[fd])
		tmp[fd] = ft_strdup("");
	ret = read(fd, buff, BUFFER_SIZE);
	while (ret >= 0)
	{
		buff[ret] = 0;
		tmp[fd] = ft_strjoin(tmp[fd], buff);
		nl = check_newline(tmp[fd]);
		if (nl != -1)
			return (get_current_line(&line, &tmp[fd], nl));
		if (!ret && !tmp[fd][0])
			break ;
		if (!ret)
			return (get_reminder(&tmp[fd], 0));
		ret = read(fd, buff, BUFFER_SIZE);
	}
	free(tmp[fd]);
	tmp[fd] = NULL;
	return (NULL);
}

char	*get_current_line(char **line, char **tmp, int nl)
{
	*line = ft_substr(*tmp, 0, nl + 1);
	*tmp = get_reminder(tmp, nl + 1);
	return (*line);
}

char	*get_reminder(char **str, int nl)
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
