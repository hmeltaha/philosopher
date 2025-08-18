/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hala <hala@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:44:37 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/18 04:51:38 by hala             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// func -- 1
// create all philosopher threads
int	start_routine(int nb_philos, pthread_t *threads, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		philos[i].id = i + 1;
		if (pthread_create(&threads[i], NULL, philo_routine, &philos[i]) != 0)
		{
			printf("Error: failed to create thread %d\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

// func -- 2
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = get_time_ms();
	while (!philo->shared->someone_died)
	{
		think(philo);
		eat(philo);
		sleep_philo(philo);
	}
	return (NULL);
}

// func -- 3
void	think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

// func -- 4
void	eat(t_philo *philo)
{
	if (lock_forks(philo))
		return ;
	eat_meal(philo);
}

// func 5
void	sleep_philo(t_philo *philo)
{
	long	start;

	start = get_time_ms();
	while (!philo->shared->someone_died && (get_time_ms()
			- start < philo->shared->time_to_sleep))
	{
		usleep(100);
	}
}
