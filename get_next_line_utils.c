/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:26:12 by ztoptas           #+#    #+#             */
/*   Updated: 2025/07/01 09:26:12 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int ch)
{
	int	i;

	i = 0;
	while (s[i] && (char)ch != s[i])
	{
		i++;
	}
	if ((char)ch == s[i])
	{
		return ((char *)(s + i));
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = ft_strlen(s1);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*joined;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	joined = malloc(s1len + s2len + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (i < s1len)
	{
		joined[i] = s1[i];
		i++;
	}
	while (i < s1len + s2len)
	{
		joined[i] = s2[i - s1len];
		i++;
	}
	joined[i] = '\0';
	return (joined);
}
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (!dst || !src)
		return (0);
	i = 0;
	j = 0;
	while (src[i])
		i++;
	if (dstsize == 0)
		return (i);
	while (j < dstsize - 1 && src[j])
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (i);
}
// ft_strjoin
char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t  i;
    char    *joined;
    size_t  s1len;
    size_t  s2len;

    if (!s1 && !s2)
        return (NULL);
    if (!s1) // s1 yoksa, s2'yi kopyala (önceki versiyonda yoktu)
        return (ft_strdup(s2));
    if (!s2) // s2 yoksa, s1'i kopyala (önceki versiyonda yoktu)
        return (ft_strdup(s1));

    s1len = ft_strlen(s1);
    s2len = ft_strlen(s2);
    joined = malloc(s1len + s2len + 1);
    if (!joined)
        return (NULL);
    i = 0;
    while (i < s1len)
    {
        joined[i] = s1[i];
        i++;
    }
    // s2'den kopyalama başlangıcı s1len'den başlar
    while (i < s1len + s2len)
    {
        joined[i] = s2[i - s1len];
        i++;
    }
    joined[i] = '\0';
    return (joined);
}