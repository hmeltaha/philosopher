/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:03:00 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/19 19:03:01 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	handle_input(int argc, char **argv)
{
	int		i;
	long	val;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!is_numeric(argv[i]))
			return (1);
		val = ft_atol(argv[i]);
		if (val <= 0 || val > INT_MAX)
			return (1);
		i++;
	}
	return (0);
}

long	ft_atol(const char *nptr)
{
	long	result;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] == ' ') || ((nptr[i] >= 9) && (nptr[i] <= 13)))
		i++;
	if ((nptr[i] == '+') || (nptr[i] == '-'))
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}

int	get_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
