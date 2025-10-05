/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:39:59 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/21 17:44:37 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// allocate memory & setup philosophers
int	init_philosophers(int nb_philos, pthread_t **threads, t_philo **philos)
{
	*threads = malloc(sizeof(pthread_t) * nb_philos);
	if (!(*threads))
		return (1);
	*philos = malloc(sizeof(t_philo) * nb_philos);
	if (!(*philos))
		return (1);
	return (0);
}

int	init_mutex_shared(t_shared **shared)
{
	if (pthread_mutex_init(&(*shared)->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*shared)->someone_died_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&(*shared)->print_mutex);
		return (1);
	}
	if (pthread_mutex_init(&(*shared)->must_eat_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&(*shared)->print_mutex);
		pthread_mutex_destroy(&(*shared)->someone_died_mutex);
		return (1);
	}
	return (0);
}

int	init_shared(t_shared **shared, char **argv, int argc)
{
	*shared = malloc(sizeof(t_shared));
	if (!*shared)
		return (1);
	(*shared)->philo_num = ft_atoi(argv[1]);
	(*shared)->time_to_die = ft_atoi(argv[2]);
	(*shared)->time_to_eat = ft_atoi(argv[3]);
	(*shared)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*shared)->must_eat_count = ft_atoi(argv[5]);
	else
		(*shared)->must_eat_count = -1;
	(*shared)->someone_died = 0;
	(*shared)->start_time_ms = get_time_ms();
	(*shared)->forks = NULL;
	if (init_mutex_shared(shared))
	{
		free(*shared);
		return (1);
	}
	return (0);
}

int	init_forks(int nb_philo, t_shared *shared)
{
	int	i;

	shared->forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!shared->forks)
		return (1);
	i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&shared->forks[i], NULL) != 0)
		{
			shared->stopped = i;
			return (1);
		}
		i++;
	}
	shared->stopped = nb_philo;
	return (0);
}
