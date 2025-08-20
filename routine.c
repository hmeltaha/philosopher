/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:44:37 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/20 19:01:19 by hmeltaha         ###   ########.fr       */
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
	if (philo->shared->philo_num == 1)
	{
		print_action(philo, "has taken a fork");
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(philo->shared->time_to_eat * 1000);
	while (!philo->shared->someone_died)
	{
		think(philo);
		eat(philo);
		sleep_philo(philo);
		usleep(100);
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
	pthread_mutex_t	*l;
	pthread_mutex_t	*r;

	if (philo->id % 2)
	{
		r = philo->right_fork;
		l = philo->left_fork;
	}
	else
	{
		l = philo->right_fork;
		r = philo->left_fork;
	}
	if (lock_forks(philo, l, r))
		return ;
	eat_meal(philo, l, r);
}

// func 5
void	sleep_philo(t_philo *philo)
{
	long	start;

	print_action(philo, "is sleeping");
	start = get_time_ms();
	while (!philo->shared->someone_died && (get_time_ms()
			- start < philo->shared->time_to_sleep))
	{
		usleep(100);
	}
}
