/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skihara <skihara@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:35:35 by skihara           #+#    #+#             */
/*   Updated: 2021/01/20 01:07:44 by skihara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	newline_check(char **stock)
{
	int	i;

	if (*stock == NULL)
		return (1);
	i = 0;
	while ((*stock)[i])
	{
		if ((*stock)[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_line(char **stock)
{
	char	*ret;
	size_t	cp_len;

	if (ft_strlen(*stock) == 0)
		return (ft_strdup(""));
	cp_len = 0;
	while ((*stock)[cp_len] && (*stock)[cp_len] != '\n')
		cp_len++;
	ret = ft_substr(*stock, 0, cp_len);
	return (ret);
}

static char	*get_stock(char **stock)
{
	char			*ret;
	unsigned int	start;
	size_t			cp_len;

	if (ft_strlen(*stock) == 0)
		return (*stock);
	start = 0;
	while ((*stock)[start] && (*stock)[start] != '\n')
		start++;
	cp_len = (ft_strlen(*stock) - start);
	ret = ft_substr(*stock, (start + 1), cp_len);
	free(*stock);
	return (ret);
}

static int	read_line(char **stock, char *buf, int fd, char **line)
{
	int	reader;

	reader = 1;
	while (!newline_check(stock) && reader != 0)
	{
		if ((reader = read(fd, buf, BUFFER_SIZE)) < 0)
		{
			free(*stock);
			free(buf);
			return (-1);
		}
		buf[reader] = '\0';
		*stock = ft_strjoin(*stock, buf);
	}
	free(buf);
	if (*stock == NULL)
		return (-1);
	*line = get_line(stock);
	*stock = get_stock(stock);
	if (*line == NULL || stock == NULL)
		return (-1);
	return (reader);
}

int			get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*stock;
	int			reader;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (-1);
	if (!(buf = malloc((size_t)BUFFER_SIZE + 1)))
		return (-1);
	*line = NULL;
	if (!stock)
		stock = ft_strdup("");
	if (stock == NULL)
	{
		free(buf);
		return (-1);
	}
	reader = read_line(&stock, buf, fd, line);
	if (reader == 0)
	{
		free(stock);
		stock = NULL;
		return (0);
	}
	return (1);
}
