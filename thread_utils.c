/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:43:51 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/20 19:01:55 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// function ---1
long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// function ---2
void	wait_philosophers(int nb_philos, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

// function ---3
void	assigns_forks(int nb_philos, t_shared **g_shared, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		(*philo)[i].shared = *g_shared;
		(*philo)[i].last_meal_time = (*g_shared)->start_time_ms;
		(*philo)[i].left_fork = &(*g_shared)->forks[i];
		if (nb_philos == 1)
			(*philo)[i].right_fork = NULL;
		else
			(*philo)[i].right_fork = &(*g_shared)->forks[(i + 1) % nb_philos];
		i++;
	}
}

// function ---4
void	*philo_routine_even(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = get_time_ms();
	usleep(philo->shared->time_to_eat);
	while (!philo->shared->someone_died)
	{
		think(philo);
		eat(philo);
		sleep_philo(philo);
	}
	return (NULL);
}
