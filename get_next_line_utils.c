/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skihara <skihara@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:47:51 by skihara           #+#    #+#             */
/*   Updated: 2021/01/20 01:04:04 by skihara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*p;
	int		i;

	if (!(p = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ans;
	size_t	i;

	if (!s)
		return (NULL);
	if (len <= 0 || ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - (size_t)start))
		len = ft_strlen(s) - (size_t)start;
	if (!(ans = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		ans[i] = s[start + i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	unsigned char *d;
	unsigned char *s;

	d = (unsigned char*)dest;
	s = (unsigned char*)src;
	if (!d && !s)
		return (NULL);
	if (s < d)
	{
		while (num--)
			*(d + num) = *(s + num);
	}
	else
	{
		while (num--)
			*d++ = *s++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ans;
	size_t	s1_len;
	size_t	s2_len;
	size_t	all_len;

	if (!s1 || !s2)
		return (ft_strdup(""));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	all_len = s1_len + s2_len;
	if (!(ans = (char*)malloc(sizeof(char) * (all_len + 1))))
	{
		free((char*)s1);
		s1 = NULL;
		return (NULL);
	}
	ft_memmove(ans, s1, s1_len);
	ft_memmove((ans + s1_len), s2, s2_len);
	ans[all_len] = '\0';
	free((char*)s1);
	s1 = NULL;
	return (ans);
}
