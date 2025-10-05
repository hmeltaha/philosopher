/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:02:42 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/19 19:02:43 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int		result;
	int		sign;
	size_t	i;

	result = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if ((nptr[i] == '+' && nptr[i + 1] != '-'))
		i++;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	result *= sign;
	return (result);
}

int	ft_isdigit(int digit)
{
	if (digit >= '0' && digit <= '9')
	{
		return (1);
	}
	else
		return (0);
}
