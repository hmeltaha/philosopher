/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:02:39 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/20 16:57:06 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_meal(t_philo *philo, pthread_mutex_t *l, pthread_mutex_t *r)
{
	long	start;

	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	print_action(philo, "is eating");
	start = get_time_ms();
	while (!philo->shared->someone_died && get_time_ms()
		- start < philo->shared->time_to_eat)
		usleep(100);
	pthread_mutex_unlock(r);
	pthread_mutex_unlock(l);
}

int	lock_forks(t_philo *philo, pthread_mutex_t *l, pthread_mutex_t *r)
{
	pthread_mutex_lock(l);
	if (philo->shared->someone_died)
	{
		pthread_mutex_unlock(l);
		return (1);
	}
	print_action(philo, "has taken a fork");
	if (r == NULL)
	{
		pthread_mutex_unlock(l);
		return (1);
	}
	pthread_mutex_lock(r);
	if (philo->shared->someone_died)
	{
		pthread_mutex_unlock(r);
		pthread_mutex_unlock(l);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}

int	lock_forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->shared->someone_died)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	if (philo->right_fork == NULL)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	if (philo->shared->someone_died)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}
