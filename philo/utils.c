/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:31:12 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/11 17:59:19 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	offset;
	size_t	src_index;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (dstsize <= d_len)
		return (dstsize + s_len);
	offset = d_len;
	src_index = 0;
	while ((*(src + src_index) != '\0') && (offset != dstsize - 1))
	{
		*(dst + offset) = *(src + src_index);
		offset++;
		src_index++;
	}
	*(dst + offset) = '\0';
	return (d_len + s_len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	delta_s;
	size_t	i;

	delta_s = 0;
	i = 0;
	while (i < n)
	{
		delta_s = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (delta_s != 0)
			return (delta_s);
		if ((unsigned char)s1[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}


char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	i = 0;
	if (needle_len == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0' && len - i >= needle_len)
	{
		if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
/*
size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;

	if (!dest && !src)
		return (0);
	dest_ptr = (char *)dest;
	src_ptr = (const char *)src;
	while (n-- != 0)
		dest_ptr[n] = src_ptr[n];
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1) + 1;
	s2 = malloc(len);
	if (s2 != NULL)
		ft_memcpy((void *)s2, (const void *)s1, len);
	return (s2);
}