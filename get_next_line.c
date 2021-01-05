/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacquel <jjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:49:20 by jjacquel          #+#    #+#             */
/*   Updated: 2020/12/05 18:41:10 by jjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	nl_finder(char *tmp_buf)
{
	int i;

	i = 0;
	while (tmp_buf[i])
	{
		if (tmp_buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	n_checker(char *tmp_buf, char **line)
{
	int	n_pos;

	n_pos = -1;
	if (tmp_buf)
	{
		if ((n_pos = nl_finder(tmp_buf)) >= 0)
		{
			tmp_buf[n_pos++] = '\0';
			*line = ft_strdup(tmp_buf);
			ft_strcpy(tmp_buf, &tmp_buf[n_pos]);
		}
		else
		{
			*line = ft_strdup(tmp_buf);
			free(tmp_buf);
		}
	}
	else
		*line = ft_strdup("");
	return (n_pos);
}

int			get_next_line(int fd, char **line)
{
	static char	*stc_buf;
	char		buf[BUFFER_SIZE + 1];
	int			n_pos;
	size_t		readed;
	char		*clr;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || (read(fd, buf, 0) < 0))
		return (-1);
	n_pos = n_checker(stc_buf, line);
	while ((n_pos == -1) && (readed = read(fd, buf, BUFFER_SIZE)))
	{
		buf[readed] = '\0';
		if ((n_pos = nl_finder(buf)) >= 0)
		{
			buf[n_pos++] = '\0';
			stc_buf = ft_strdup(&buf[n_pos]);
		}
		clr = *line;
		*line = ft_strjoin(*line, buf);
		free(clr);
	}
	if (n_pos != -1)
		return (1);
	stc_buf = NULL;
	return (0);
}
