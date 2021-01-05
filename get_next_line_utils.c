/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacquel <jjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:20:41 by jjacquel          #+#    #+#             */
/*   Updated: 2021/01/05 19:30:49 by jjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*ft_strdup(const char *s1)
{
	char			*new;
	unsigned int	i;

	if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (0);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lenght;
	size_t	z;
	char	*temp;

	if (!s1 || !s2)
		return (NULL);
	lenght = ft_strlen(s1) + ft_strlen(s2);
	if (!(temp = (char*)malloc((lenght + 1) * sizeof(char))))
		return (NULL);
	z = 0;
	while (s1[z])
	{
		temp[z] = s1[z];
		z++;
	}
	z = 0;
	while (s2[z])
	{
		temp[ft_strlen(s1) + z] = s2[z];
		z++;
	}
	temp[lenght] = '\0';
	return (temp);
}

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
