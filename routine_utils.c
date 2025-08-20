/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:44:35 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/20 18:12:51 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_philos_ate_enough(t_shared *shared)
{
	int		i;
	bool	all_ate;

	all_ate = true;
	all_ate = true;
	if (shared->must_eat_count == -1)
		return (false);
	pthread_mutex_lock(&shared->must_eat_mutex);
	i = 0;
	while (i < shared->philo_num)
	{
		if (shared->philos[i].meals_eaten < shared->must_eat_count)
		{
			all_ate = false;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&shared->must_eat_mutex);
	return (all_ate);
}

void	mutex_destroy_all(pthread_t **threads, t_shared **shared)
{
	(void)threads;
	pthread_mutex_destroy(&(*shared)->print_mutex);
	pthread_mutex_destroy(&(*shared)->must_eat_mutex);
	pthread_mutex_destroy(&(*shared)->someone_died_mutex);
}

void	cleanup(t_shared **shared, pthread_t **threads, t_philo **philos)
{
	int	i;

	if (!shared || !(*shared))
		return ;
	if ((*shared)->forks)
	{
		i = -1;
		while (++i < (*shared)->stopped)
			pthread_mutex_destroy(&(*shared)->forks[i]);
		free((*shared)->forks);
	}
	mutex_destroy_all(threads, shared);
	if (philos && *philos)
	{
		free(*philos);
		*philos = NULL;
	}
	if (threads && *threads)
	{
		free(*threads);
		*threads = NULL;
	}
	free(*shared);
	*shared = NULL;
}
