/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:20:28 by modat             #+#    #+#             */
/*   Updated: 2025/08/13 15:42:03 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest_str, const void *src_str, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*src;

	ptr = (unsigned char *)dest_str;
	src = (unsigned char *)src_str;
	if (!dest_str && !src_str)
	{
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		ptr[i] = src[i];
		i++;
	}
	return (dest_str);
}
