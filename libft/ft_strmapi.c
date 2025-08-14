/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:02:07 by modat             #+#    #+#             */
/*   Updated: 2025/08/13 15:41:33 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	passfunc(unsigned int i, char amended_s)
{
	if ((amended_s >= 'a' && amended_s <= 'z'))
		return (amended_s - 32);
	else
		i++;
	return (amended_s);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*amended_s;
	size_t			slen;

	i = 0;
	if (!s || !f)
		return (NULL);
	slen = ft_strlen(s);
	amended_s = (char *)malloc((slen + 1) * sizeof(char));
	if (!amended_s)
		return (NULL);
	while (s[i] != '\0')
	{
		amended_s[i] = (*f)(i, s[i]);
		i++;
	}
	amended_s[i] = '\0';
	return (amended_s);
}
