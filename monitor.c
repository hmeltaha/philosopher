/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:02:45 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/19 19:02:46 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_dead(t_shared *shared, int i, long now)
{
	long	time_since_meal;

	time_since_meal = now - shared->philos[i].last_meal_time;
	if (time_since_meal > shared->time_to_die)
	{
		pthread_mutex_lock(&shared->print_mutex);
		printf("%ld %d died 💀\n", now - shared->start_time_ms,
			shared->philos[i].id);
		pthread_mutex_unlock(&shared->print_mutex);
		pthread_mutex_lock(&shared->someone_died_mutex);
		shared->someone_died = 1;
		pthread_mutex_unlock(&shared->someone_died_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_ate(t_shared *shared)
{
	if (all_philos_ate_enough(shared))
	{
		pthread_mutex_lock(&shared->someone_died_mutex);
		shared->someone_died = 1;
		pthread_mutex_unlock(&shared->someone_died_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_shared	*shared;
	long		now;
	int			i;

	shared = (t_shared *)arg;
	while (!shared->someone_died)
	{
		now = get_time_ms();
		i = 0;
		while (i < shared->philo_num && !shared->someone_died)
		{
			if (check_philo_dead(shared, i, now))
				return (NULL);
			i++;
		}
		if (check_all_ate(shared))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
