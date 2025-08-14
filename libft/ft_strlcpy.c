/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:04:24 by modat             #+#    #+#             */
/*   Updated: 2025/08/13 15:41:12 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	x;

	x = 0;
	if (size > 0)
	{
		while (src[x] != '\0' && x < size - 1)
		{
			dest[x] = src[x];
			x++;
		}
		dest[x] = '\0';
	}
	ft_strlen(src);
	return (ft_strlen(src));
}
